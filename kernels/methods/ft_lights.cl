#ifndef FT_LIGHTS_CL
# define FT_LIGHTS_CL

# include "../kernel.h"

bool					ft_shadow(t_ray main_ray, t_vec3 l, const __constant t_obj *objs);
void					ft_light(t_color *c, t_ray ray,
								const __constant t_light *lights,
								const __constant t_obj *obj,
								const __constant t_obj *objs,
								const __constant t_tex *textures,
								t_color color);
void					ft_light_toon(t_color *c, t_ray ray,
								const __constant t_light *lights,
								const __constant t_obj *objs,
								t_color color);

# include "ft_textures.cl"

bool					ft_shadow(__private t_ray main_ray,
								__private t_vec3 l,
								const __constant t_obj *objs)
{
	// return (1);
	__private t_ray		ray;
	__private t_dec		limit;

	limit = sqrt(l.x * l.x + l.y * l.y + l.z * l.z);
	ft_init_ray(&ray, main_ray.p, fast_normalize(l));
	ft_raycast(objs, &ray, main_ray.id);
	if (ray.id >= 0 && ray.t.x < limit)
		return (0);
	return (1);
}

void					ft_light(__private t_color *c,
								__private t_ray ray,
								const __constant t_light *lights,
								const __constant t_obj *obj,
								const __constant t_obj *objs,
								const __constant t_tex *textures,
								__private t_color color)
{
	__private t_vec3	l; // obj -> light vector
	__private t_vec3	r; // reflect vector
	__private float		diffuse;
	__private float		spec;
	__private bool		shadow;

	while (lights->intensity >= 0)
	{
		l = lights->dir * -1;
		if (l.x + l.y + l.z == 0) // If light isn't directional, use position
			l = lights->pos - ray.p;
		shadow = ft_shadow(ray, l, objs);
		l = fast_normalize(l);
		diffuse = dot(ray.normal, l);
		if (shadow && diffuse > 0.0)
		{
			// Add diffuse light :
			*c = ft_color_add(*c, 1, color, diffuse * lights->intensity);
			if (obj->spec > 0)
			{
				// Compute reflected ray :
				r = 2 * dot(ray.normal, l) * ray.normal - l;
				// Compute spec amount and add specular light :
				spec = pow(dot(r, ray.normal), obj->spec);
				if (obj->texture_spec >= 0)
					spec *= ft_texture_spec(&ray, obj, textures + obj->texture_spec);
				*c = ft_color_add_const(*c, 1, &(lights->color), spec * lights->intensity);
			}
		}
		lights++;
	}
}

void					ft_light_toon(__private t_color *c,
								__private t_ray ray,
								const __constant t_light *lights,
								const __constant t_obj *objs,
								__private t_color color)
{
	__private t_vec3	l; // obj -> light vector
	__private float		diffuse;
	__private bool		shadow;

	while (lights->intensity >= 0)
	{
		l = lights->dir * -1;
		if (l.x + l.y + l.z == 0) // If light isn't directional, use position
			l = lights->pos - ray.p;
		shadow = ft_shadow(ray, l, objs);
		l = fast_normalize(l);
		diffuse = dot(ray.normal, l);
		if (diffuse < 0.05)
			diffuse = 0.05;
		else if (diffuse >= 0.05 && diffuse < 0.6)
			diffuse = 0.4;
		else if (diffuse >= 0.6 && diffuse < 0.9)
			diffuse = 0.6;
		else
			diffuse = 1;
		if (shadow && diffuse > 0.0)
		{
			// Add diffuse light :
			*c = ft_color_add(*c, 1, color, diffuse * lights->intensity);
		}
		lights++;
	}
}

#endif
