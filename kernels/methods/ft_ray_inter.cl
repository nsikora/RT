#ifndef FT_RAY_INTER_CL
# define FT_RAY_INTER_CL

# include "../kernel.h"

void					ft_raycast_cyl(const __constant t_obj *obj, t_ray *ray, int id);
void					ft_raycast_cone(const __constant t_obj *obj, t_ray *ray, int id);
void					ft_raycast_plane(const __constant t_obj *obj, t_ray *ray, int id);
int						ft_raycast_plane_private(t_obj *obj, t_ray *ray, int id);
void					ft_raycast_sphere(const __constant t_obj *obj, t_ray *ray, int id);
void					ft_raycast_cube(const __constant t_obj *obj, t_ray *ray, int id);

# include "ft_perturbation.cl"

void					ft_raycast_sphere(const __constant t_obj *obj,
										__private t_ray *ray,
										__private int id)
{
	__private t_vec3	origin_pos;
	__private t_vec3	eq;
	__private t_vec2	t;

	origin_pos = ray->origin - obj->pos;
	eq.x = dot(ray->dir, ray->dir);
	eq.y = dot(ray->dir, origin_pos) * 2;
	eq.z = dot(origin_pos, origin_pos) - obj->scl.x * obj->scl.x;
	t = ft_solve_quadratic(eq);
	ft_set_obj(t, ray, id, ID_SPHERE);
}

void					ft_raycast_plane(const __constant t_obj *obj,
										__private t_ray *ray,
										__private int id)
{
	__private t_vec2	t;
	__private t_vec3	p;
	__private t_vec3	v;
	__private t_dec		test;

	test = dot(ray->dir, obj->dir);
	if (test == 0)
		return ;
	t = dot((obj->pos - ray->origin), obj->dir) / test;
	p = ray->origin + ray->dir * t.x;
	if (obj->scl.x > 0)
	{
		v = p - obj->pos;
		if (obj->scl.y > 0)
		{
			v = ft_rotate_from_dir(v, obj->dir, (t_vec3){0, 0, 1});
			if (!(v.x < obj->scl.x / 2 && v.x > -obj->scl.x / 2 &&
					v.y < obj->scl.y / 2 && v.y > -obj->scl.y / 2))
				t = -1;
		}
		else if (dot(v, v) > obj->scl.x * obj->scl.x)
			t = -1;
	}
	ft_set_obj(t, ray, id, ID_PLANE);
}

int						ft_raycast_plane_private(__private t_obj *obj,
												__private t_ray *ray,
												__private int id)
{
	__private t_vec2	t;
	__private t_vec3	p;
	__private t_vec3	v;
	__private t_dec		test;

	test = dot(ray->dir, obj->dir);
	if (test == 0)
		return (0);
	t = dot((obj->pos - ray->origin), obj->dir) / test;
	p = ray->origin + ray->dir * t.x;
	if (obj->scl.x > 0)
	{
		v = p - obj->pos;
		if (obj->scl.y > 0)
		{
			v = ft_rotate_from_dir(v, obj->dir, (t_vec3){0, 0, 1});
			if (!(v.x < obj->scl.x / 2 && v.x > -obj->scl.x / 2 &&
					v.y < obj->scl.y / 2 && v.y > -obj->scl.y / 2))
				t = -1;
		}
		else if (dot(v, v) > obj->scl.x * obj->scl.x)
			t = -1;
	}
	return (ft_set_obj(t, ray, id, ID_PLANE));
}

static void				ft_raycast_cube_plane(__private t_obj *obj,
											__private t_ray *ray,
											__private int id)
{
	if (ft_raycast_plane_private(obj, ray, id))
	{
		ray->normal = obj->dir;
		ray->type = ID_CUBE;
	}
}

void					ft_raycast_cube(const __constant t_obj *obj,
										__private t_ray *ray,
										__private int id)
{
	__private t_obj		plane;

	plane.scl = (t_vec3){obj->scl.x, obj->scl.z, 0};

	plane.dir = (t_vec3){0, 1, 0};
	plane.pos = obj->pos + plane.dir * (obj->scl.y / 2);
	ft_raycast_cube_plane(&plane, ray, id);

	plane.dir = (t_vec3){0, -1, 0};
	plane.pos = obj->pos + plane.dir * (obj->scl.y / 2);
	ft_raycast_cube_plane(&plane, ray, id);

	plane.scl = (t_vec3){obj->scl.z, obj->scl.y, 0};

	plane.dir = (t_vec3){-1, 0, 0};
	plane.pos = obj->pos + plane.dir * (obj->scl.x / 2);
	ft_raycast_cube_plane(&plane, ray, id);

	plane.dir = (t_vec3){1, 0, 0};
	plane.pos = obj->pos + plane.dir * (obj->scl.x / 2);
	ft_raycast_cube_plane(&plane, ray, id);

	plane.scl = (t_vec3){obj->scl.x, obj->scl.y, 0};

	plane.dir = (t_vec3){0, 0, 1};
	plane.pos = obj->pos + plane.dir * (obj->scl.z / 2);
	ft_raycast_cube_plane(&plane, ray, id);

	plane.dir = (t_vec3){0, 0, -1};
	plane.pos = obj->pos + plane.dir * (obj->scl.z / 2);
	ft_raycast_cube_plane(&plane, ray, id);
}

void					ft_raycast_cone(const __constant t_obj *obj,
										__private t_ray *ray,
										__private int id)
{
	__private t_vec3	eq;
	__private t_vec2	t;

	__private t_vec3	p[2];

	__private t_vec3	d_pos;
	__private t_vec2	XY;
	__private t_vec3	MN[2];
	__private t_vec2	cos2_sin2;

	__private t_obj		cap;

	d_pos = ray->origin - obj->pos;
	cos2_sin2.x = cos(obj->scl.x) * cos(obj->scl.x);
	cos2_sin2.y = sin(obj->scl.x) * sin(obj->scl.x);

	XY.x = dot(ray->dir, obj->dir);
	XY.y = dot(d_pos   , obj->dir);

	MN[0] = ray->dir - (XY.x * obj->dir);
	MN[1] = d_pos    - (XY.y * obj->dir);

	eq.x = cos2_sin2.x * dot(MN[0], MN[0]) - cos2_sin2.y * (XY.x * XY.x);
	eq.z = cos2_sin2.x * dot(MN[1], MN[1]) - cos2_sin2.y * (XY.y * XY.y);
	eq.y = 2 * cos2_sin2.x * dot(MN[0], MN[1])
		 - 2 * cos2_sin2.y * XY.x * XY.y;
	t = ft_solve_quadratic(eq);
	if (obj->scl.y > 0 && (t.x > 0 || t.y > 0))
	{
		p[0] = ray->origin + ray->dir * (t.x > 0 ? t.x : t.y);
		p[1] = obj->pos + obj->dir * obj->scl.y;
		if (dot((p[0] - obj->pos), obj->dir) < 0 || !(dot(obj->dir, p[0] - p[1]) < 0))
			t = -1;
		ft_set_obj(t, ray, id, ID_CONE);
		cap.pos = p[1];
		cap.dir = obj->dir;
		cap.scl = (t_vec3){tan(obj->scl.x) * obj->scl.y, -1, -1};
		ft_raycast_plane_private(&cap, ray, id);
	}
	else
		ft_set_obj(t, ray, id, ID_CONE);
}

void					ft_raycast_cyl(const __constant t_obj *obj,
									__private t_ray *ray,
									__private int id)
{
	__private t_vec3	eq;
	__private t_vec2	t;

	__private t_vec3	p[3];

	__private t_vec3	d_pos;
	__private t_vec2	XY;
	__private t_vec3	MN[2];

	__private t_obj		cap;

	d_pos = ray->origin - obj->pos;
	XY.x = dot(ray->dir, obj->dir);
	XY.y = dot(d_pos   , obj->dir);

	MN[0] = ray->dir - (XY.x * obj->dir);
	MN[1] = d_pos    - (XY.y * obj->dir);

	eq.x = dot(MN[0], MN[0]);
	eq.z = dot(MN[1], MN[1]) - obj->scl.x * obj->scl.x;
	eq.y = 2 * dot(MN[0], MN[1]);
	t = ft_solve_quadratic(eq);
	if (obj->scl.y > 0 && (t.x > 0 || t.y > 0))
	{
		p[1] = obj->pos - obj->dir * (obj->scl.y / 2);
		p[2] = obj->pos + obj->dir * (obj->scl.y / 2);
		p[0] = ray->origin + ray->dir * (t.x > 0 ? t.x : t.y);
		if (!(dot(obj->dir, p[0] - p[1]) > 0) || !(dot(obj->dir, p[0] - p[2]) < 0))
			t = -1;
		ft_set_obj(t, ray, id, ID_CYLINDER);
		cap.pos = p[1];
		cap.dir = -(obj->dir);
		cap.scl = (t_vec3){obj->scl.x, -1, -1};
		ft_raycast_plane_private(&cap, ray, id);
		cap.pos = p[2];
		cap.dir = obj->dir;
		cap.scl = (t_vec3){obj->scl.x, -1, -1};
		ft_raycast_plane_private(&cap, ray, id);
	}
	else
		ft_set_obj(t, ray, id, ID_CYLINDER);
}

/*
	if (obj->scl.y > 0 && (t.x > 0 || t.y > 0))
	{
		p1 = obj->pos - obj->dir * (obj->scl.y / 2);
		p2 = obj->pos + obj->dir * (obj->scl.y / 2);
		p = ray->origin + ray->dir * (t.x > 0 ? t.x : t.y);
		if (dot(obj->dir, p - p1) <= 0 || dot(obj->dir, p - p2) >= 0)
			t = -1;
		cap.pos = p2;
		cap.dir = obj->dir;
		cap.scl = (t_vec3){obj->scl.x, -1, -1};
		t_cap = ft_raycast_plane(cap, ray);
		if (t_cap.x > 0 && (t.x < 0 || t.x > t_cap.x))
			t.x = t_cap.x;
		cap.pos = p1;
		cap.dir = -(obj->dir);
		cap.scl = (t_vec3){obj->scl.x, -1, -1};
		t_cap = ft_raycast_plane(cap, ray);
		if (t_cap.x > 0 && (t.x < 0 || t.x > t_cap.x))
			t.x = t_cap.x;
		ft_set_obj(t, ray, id);
	}
	else
*/

#endif
