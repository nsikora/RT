#ifndef FT_TEXTURES_CL
# define FT_TEXTURES_CL

# include "../kernel.h"

t_vec2						ft_spheric_pos(t_vec3 pos, const __constant t_obj *obj, int width, int height);
t_vec2						ft_cylindric_pos(t_vec3 pos, const __constant t_obj *obj, int width, int height);
t_vec2						ft_planar_pos(t_vec3 pos, const __constant t_obj *obj, int width, int height);
t_color						ft_texture_color(t_ray ray, const __constant t_obj *obj, const __constant t_tex *tex);
void						ft_texture_norm(t_ray *ray, const __constant t_obj *obj, const __constant t_tex *tex);
t_dec						ft_texture_spec(t_ray *ray, const __constant t_obj *obj, const __constant t_tex *tex);
int							ft_2D_checkerboard(t_ray *ray, const __constant t_obj *obj);
t_color						ft_texture_perlin(t_ray *ray, const __constant t_obj *obj);

# include "ft_perturbation.cl"

t_vec2						ft_spheric_pos(t_vec3 pos, const __constant t_obj *obj, int width, int height)
{
	__private t_vec2		spheric;

	pos = ft_rotate_from_dir(pos - obj->pos, obj->dir, (t_vec3){0, 1, 0});

	spheric.x = (atan(pos.z / pos.x) + M_PI_2) / M_PI;
	spheric.y = 1 - acos(normalize(pos).y) / M_PI;

	spheric.x = floor(spheric.x * (width / 2));
	if (pos.x < 0)
		spheric.x += width / 2;
	spheric.y = floor(spheric.y * height);

	spheric.x = (int)(spheric.x + obj->texture_xoff) % width;
	spheric.y = (int)(spheric.y + obj->texture_yoff) % height;
	return (spheric);
}

t_vec2						ft_planar_pos(t_vec3 pos, const __constant t_obj *obj, int width, int height)
{
	__private t_vec2		planar;

	if (obj->type == ID_PLANE)
		pos = ft_rotate_from_dir(pos - obj->pos, obj->dir, (t_vec3){0, 0, 1});
	else
		pos = ft_rotate_from_dir(pos - obj->pos, obj->dir, (t_vec3){0, 1, 0});

	planar.x = 1 - pos.x / ((float)width / height) / 20 + 0.5;
	planar.y = pos.y / 10 + 0.5;

	planar.x = floor(planar.x * width) / obj->texture_scl;
	planar.y = floor(planar.y * height) / obj->texture_scl;

	planar.x = (int)(planar.x + obj->texture_xoff) % width;
	planar.y = (int)(planar.y + obj->texture_yoff) % height;
	if (planar.x < 0)
		planar.x = width + planar.x;
	if (planar.y < 0)
		planar.y = height + planar.y;
	return (planar);
}

t_vec2						ft_cylindric_pos(t_vec3 pos, const __constant t_obj *obj, int width, int height)
{
	__private t_vec2		cylindric;

	pos = ft_rotate_from_dir(pos - (obj->pos), obj->dir, (t_vec3){0, 1, 0});

	cylindric.y = pos.y;
	if (obj->type == ID_SPHERE || (obj->type == ID_CYLINDER && obj->scl[1] <= 0))
		cylindric.y /= (2 * M_PI * obj->scl[0] * ((float)height / width));
	else if (obj->type == ID_CYLINDER && obj->scl[1] > 0)
		cylindric.y = cylindric.y / obj->scl[1] - 0.5;
	else if (obj->type == ID_CONE)
		cylindric.y /= obj->scl[1] > 0 ? obj->scl[1] : (2 * M_PI * tan(obj->scl[0]) * ((float)height / width));
	if (obj->type == ID_SPHERE)
		cylindric.y -= obj->scl[0] / 2;
	cylindric.x = (atan(pos.z / pos.x) + M_PI_2) / M_PI;


	cylindric.x = floor(cylindric.x * (width / 2));
	if (pos.x < 0)
		cylindric.x += width / 2;
	cylindric.y = floor(cylindric.y * height) / obj->texture_scl;

	cylindric.x = (int)(cylindric.x + obj->texture_xoff) % width;
	cylindric.y = (int)(cylindric.y + obj->texture_yoff) % height;
	if (cylindric.y < 0)
		cylindric.y = height + cylindric.y;
	return (cylindric);
}

t_color						ft_texture_color(t_ray ray, const __constant t_obj *obj, const __constant t_tex *tex)
{
	__private t_vec2		t;

	if (tex->pixels == 0)
		return (obj->color);
	if (obj->texture_mode == 0)
		t = ft_spheric_pos(ray.p, obj, tex->width, tex->height);
	else if (obj->texture_mode == 1)
		t = ft_cylindric_pos(ray.p, obj, tex->width, tex->height);
	else if (obj->texture_mode == 2)
		t = ft_planar_pos(ray.p, obj, tex->width, tex->height);
	else
		return (obj->color);
	return (tex->pixels[(int)(t.x + t.y * tex->width)]);
}

void						ft_texture_norm(t_ray *ray, const __constant t_obj *obj, const __constant t_tex *tex)
{
	__private t_vec2		t;
	__private t_dec			amount;
	__private t_color		color;
	__private t_vec3		normal;

	if (tex->pixels == 0)
		return ;
	if (obj->texture_mode == 0)
		t = ft_spheric_pos(ray->p, obj, tex->width, tex->height);
	else if (obj->texture_mode == 1)
		t = ft_cylindric_pos(ray->p, obj, tex->width, tex->height);
	else if (obj->texture_mode == 2)
		t = ft_planar_pos(ray->p, obj, tex->width, tex->height);
	else
		return ;
	color = tex->pixels[(int)(t.x + t.y * tex->width)];
	amount = (color.byte[0] + color.byte[1] + color.byte[2]) / 3 / 255.0 * 2 - 1;
	normal = normalize((t_vec3){color.byte[0] / 255.0 * 2 - 1, color.byte[1] / 255.0 * 2 - 1, color.byte[2] / 255.0 * 2 - 1});
	ray->normal = ft_rotate_from_dir(ray->normal, (t_vec3){0, 0, 1}, normal);
	ray->normal.x *= -1;
	ray->normal.y *= -1;
}

t_dec						ft_texture_spec(t_ray *ray, const __constant t_obj *obj, const __constant t_tex *tex)
{
	__private t_vec2		t;
	__private t_dec			a;

	if (tex->pixels == 0)
		return (1);
	if (obj->texture_mode == 0)
		t = ft_spheric_pos(ray->p, obj, tex->width, tex->height);
	else if (obj->texture_mode == 1)
		t = ft_cylindric_pos(ray->p, obj, tex->width, tex->height);
	else if (obj->texture_mode == 2)
		t = ft_planar_pos(ray->p, obj, tex->width, tex->height);
	else
		return (1);
	a = (tex->pixels[(int)(t.x + t.y * tex->width)].byte[0] / 255.0
		+ tex->pixels[(int)(t.x + t.y * tex->width)].byte[1] / 255.0
		+ tex->pixels[(int)(t.x + t.y * tex->width)].byte[2] / 255.0) / 3;
	return (a);
}

int							ft_2D_checkerboard(t_ray *ray, const __constant t_obj *obj)
{
	__private float2		t;
	int						i;

	if (obj->texture_mode == 0)
		t = ft_spheric_pos(ray->p, obj, 50, 50);
	else if (obj->texture_mode == 1)
		t = ft_cylindric_pos(ray->p, obj, 50, 50);
	else if (obj->texture_mode == 2)
		t = ft_planar_pos(ray->p, obj, 50, 50);
	else
		return (obj->color.rgb);

	i = ((int)t.x + (int)t.y) % 2;
	if (i == 0)
		return (0xFF000000);
	else
		return (0xFFFFFFFF);
}

t_color						ft_texture_perlin(t_ray *ray, const __constant t_obj *obj)
{
	__private float2		t;
	__private t_color		color;
	__private int			grey;

	if (obj->texture_mode == 0)
		t = ft_spheric_pos(ray->p, obj, 1024, 1024);
	else if (obj->texture_mode == 1)
		t = ft_cylindric_pos(ray->p, obj, 1024, 1024);
	else if (obj->texture_mode == 2)
		t = ft_planar_pos(ray->p, obj, 1024, 1024);
	else
		return (obj->color);
	grey = (ft_2D_perlin_noise(t, 10) + 1) * 127.5;
	color.byte4 = grey;
	color.byte[3] = 255;
	return (color);
}

#endif
