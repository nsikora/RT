#ifndef FT_RAYCAST_CL
# define FT_RAYCAST_CL

# include "../kernel.h"

void					ft_raycast(const __constant t_obj *obj, t_ray *ray, int ignore);
int						ft_set_obj(t_vec2 t, t_ray *ray, int id, int type);
void					ft_init_ray(t_ray *ray, t_vec3 origin, t_vec3 dir);
t_vec2					ft_solve_quadratic(t_vec3 eq);
void					ft_compute_p_normal(t_ray *ray, const __constant t_obj *obj, bool yforce);
bool					ft_closest_obj(t_vec2 t, t_ray *ray, int id);
void					ft_compute_normal(t_ray *ray, const __constant t_obj *obj);

# include "ft_ray_inter.cl"

void					ft_compute_normal(__private t_ray *ray,
											const __constant t_obj *obj)
{
	__private t_dec		tmp;
	__private t_vec3	rotation;

	if (ray->type == ID_SPHERE)
		ray->normal = fast_normalize(ray->p - obj->pos);
	else if (ray->type == ID_PLANE)
		ray->normal = obj->dir * (dot(ray->dir, obj->dir) < 0 ? 1 : -1);
	else if (ray->type == ID_CYLINDER || ray->type == ID_CONE)
	{
		tmp = dot((ray->p - obj->pos), obj->dir);
		ray->normal = ray->p - (obj->pos + tmp * obj->dir);
		ray->normal = fast_normalize(ray->normal);
		if (ray->type == ID_CONE)
		{
			// Rotate normal towards obj->dir * (tmp > 0 ? 1 : -1)
			rotation = cross(obj->dir * (tmp > 0 ? 1 : -1), ray->normal);
			ray->normal = ray->normal * cos(obj->scl.x)
				+ cross(rotation, ray->normal) * sin(obj->scl.x)
				+ rotation * dot(rotation, ray->normal) * (1 - cos(obj->scl.x));
		}
		// ft_apply_sin_to_norm(ray);
	}
}

void					ft_compute_p_normal(__private t_ray *ray,
											const __constant t_obj *obj,
											__private bool yforce)
{
	__private bool		rev = false;
	__private t_dec		tmp;
	__private t_vec3	rotation;

	if (!yforce && ray->t.x > 0)
		ray->p = ray->origin + ray->dir * ray->t.x;
	else
	{
		rev = true;
		ray->p = ray->origin + ray->dir * ray->t.y;
	}
	if (ray->type == ID_SPHERE)
		ray->normal = fast_normalize(ray->p - obj->pos);
	else if (ray->type == ID_PLANE)
		ray->normal = obj->dir * (dot(ray->dir, obj->dir) < 0 ? 1 : -1);
	else if (ray->type == ID_CYLINDER || ray->type == ID_CONE)
	{
		tmp = dot((ray->p - obj->pos), obj->dir);
		ray->normal = ray->p - (obj->pos + tmp * obj->dir);
		ray->normal = fast_normalize(ray->normal);
		if (ray->type == ID_CONE)
		{
			// Rotate normal towards obj->dir * (tmp > 0 ? 1 : -1)
			rotation = cross(obj->dir * (tmp > 0 ? 1 : -1), ray->normal);
			ray->normal = ray->normal * cos(obj->scl.x)
				+ cross(rotation, ray->normal) * sin(obj->scl.x)
				+ rotation * dot(rotation, ray->normal) * (1 - cos(obj->scl.x));
		}
		// ft_apply_sin_to_norm(ray);
	}
	if (rev)
		ray->normal *= -1;
}

t_vec2					ft_solve_quadratic(__private t_vec3 eq)
{
	__private t_vec2	r;
	__private t_dec		d;

	d = sqrt(eq.y * eq.y - 4 * eq.x * eq.z);
	if (d < 0)
		return (-1);
	r = (-(eq.y) - d) / (2 * eq.x);
	if (d > 0)
		r.y = (-(eq.y) + d) / (2 * eq.x);
	return (r);
}

void					ft_init_ray(__private t_ray *ray,
									__private t_vec3 origin,
									__private t_vec3 dir)
{
	ray->origin = origin;
	ray->dir = dir;
	ray->id = -1;
	ray->t = -1;
}

int						ft_set_obj(t_vec2 t, t_ray *ray, int id, int type)
{
	if (t.x > 0 && ((ray->id < 0) || ((ray->t.x <= 0 || ray->t.x > t.x) && (ray->t.y <= 0 || ray->t.y > t.x))))
	{
		ray->id = id;
		ray->t = t;
		ray->type = type;
		return (1);
	}
	else if (t.y > 0 && ((ray->id < 0) || ((ray->t.x <= 0 || ray->t.x > t.y) && (ray->t.y <= 0 || ray->t.y > t.y))))
	{
		ray->id = id;
		ray->t = t;
		ray->type = type;
		return (1);
	}
	return (0);
}

void					ft_raycast(const __constant t_obj *obj,
									__private t_ray *ray,
									__private int	ignore)
{
	__private int		id;

	if (!obj || !ray)
		return ;
	id = 0;
	while (obj->type != -1)
	{
		if (id != ignore)
		{
			if (obj->type == ID_SPHERE)
				ft_raycast_sphere(obj, ray, id);
			else if (obj->type == ID_CONE)
				ft_raycast_cone(obj, ray, id);
			else if (obj->type == ID_PLANE)
				ft_raycast_plane(obj, ray, id);
			else if (obj->type == ID_CYLINDER)
				ft_raycast_cyl(obj, ray, id);
			else if (obj->type == ID_CUBE)
				ft_raycast_cube(obj, ray, id);
		}
		obj++;
		id++;
	}
}

#endif