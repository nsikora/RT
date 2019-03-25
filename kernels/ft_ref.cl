#include "./kernels/kernel.h"
#include "./kernels/methods/ft_raycast.cl"
#include "./kernels/methods/ft_textures.cl"
#include "./kernels/methods/ft_color.cl"
#include "./kernels/methods/ft_lights.cl"

static t_ray				ft_reflect(const __constant t_obj		*objs,
										const __constant t_light	*lights,
										const __constant t_tex		*textures,
										__private t_ray				ray)
{
	__private t_ray			reflect;
	__private t_vec3		dir;

	dir = fast_normalize(ray.dir - 2 * dot(ray.normal, ray.dir) * ray.normal);
	ft_init_ray(&reflect, ray.p, dir);
	ft_raycast(objs, &reflect, ray.id);
	if (reflect.id >= 0)
	{
		ft_compute_p_normal(&reflect, objs + reflect.id, false);
		if (objs[reflect.id].texture_norm >= 0)
			ft_texture_norm(&reflect, objs + reflect.id, textures + objs[reflect.id].texture_norm);
	}
	return (reflect);
}

static t_ray				ft_refract(const __constant t_obj		*objs,
										const __constant t_light	*lights,
										const __constant t_tex		*textures,
										__private t_ray				ray)
{
	__private t_ray			refract;
	__private t_vec3		dir;
	__private t_dec			r, c;

	r = ray.t.x >= 0 ? 1 / objs[ray.id].refract : objs[ray.id].refract / 1;
	c = -dot(ray.normal, ray.dir);
	dir = r * ray.dir + (r * c - sqrt(1 - r * r * (1 - c * c))) * ray.normal;
	ft_init_ray(&refract, ray.p, dir);
	ft_raycast(objs, &refract, ray.id);
	if (refract.id >= 0)
	{
		ft_compute_p_normal(&refract, objs + refract.id, false);
		if (objs[refract.id].texture_norm >= 0)
			ft_texture_norm(&refract, objs + refract.id, textures + objs[refract.id].texture_norm);
	}
	return (refract);
}

__kernel void				ft_ref(const __private t_dec		ambient,
									const __constant t_obj		*objs,
									const __constant t_light	*lights,
									const __constant t_tex		*textures,
									__global t_color			*img,
									__global t_ray				*rays,
									__private int				limit,
									__local t_ray				*ref_rays,
									__local t_color				*colors)
{
	if (limit < 1)
		return ;
	const __private int		id = get_global_id(0);
	const __private t_ray	base_ray = rays[id];

	__private int			index = -1;
	__private int			maxi = pow((float)2, (float)limit) - 2;
	__private t_ray			ray = base_ray;
	__private t_vec3		coeffs;

	__private t_color		c;
	__private t_color		current;
	__private t_color		reflection;
	__private t_color		transparency;

	while (index < maxi)
	{
		if (ray.id >= 0)
		{
			if (objs[ray.id].reflect > 0)
				ref_rays[index * 2 + 2] = ft_reflect(objs, lights, textures, ray);
			else
				ref_rays[index * 2 + 2].id = -1;
			if (objs[ray.id].trans > 0)
				ref_rays[index * 2 + 3] = ft_refract(objs, lights, textures, ray);
			else
				ref_rays[index * 2 + 3].id = -1;
		}
		else
		{
			ref_rays[index * 2 + 2].id = -1;
			ref_rays[index * 2 + 3].id = -1;
		}
		index++;
		ray = ref_rays[index];
	}

	maxi = pow((float)2, (float)(limit - 1)) - 2;
	while (--index >= 0)
	{
		if (ref_rays[index * 2 + 2].id >= 0)
		{
			if (index < maxi)
				reflection = colors[index * 2 + 2];
			else
			{
				if (objs[ref_rays[index * 2 + 2].id].texture >= 0)
					c = ft_texture_color(ref_rays[index * 2 + 2], objs + ref_rays[index * 2 + 2].id, textures + objs[ref_rays[index * 2 + 2].id].texture);
				else
					c = objs[ref_rays[index * 2 + 2].id].color;
				reflection = ft_color_bright(c, ambient);
				ft_light(&reflection, ref_rays[index * 2 + 2], lights, objs + ref_rays[index * 2 + 2].id, objs, textures, c);
			}
		}
		else
			reflection.rgb = 0xFF000000;
		if (ref_rays[index * 2 + 3].id >= 0)
		{
			if (index < maxi)
				transparency = colors[index * 2 + 3];
			else
			{
				if (objs[ref_rays[index * 2 + 3].id].texture >= 0)
					c = ft_texture_color(ref_rays[index * 2 + 3], objs + ref_rays[index * 2 + 3].id, textures + objs[ref_rays[index * 2 + 3].id].texture);
				else
					c = objs[ref_rays[index * 2 + 3].id].color;
				transparency = ft_color_bright(c, ambient);
				ft_light(&transparency, ref_rays[index * 2 + 3], lights, objs + ref_rays[index * 2 + 3].id, objs, textures, c);
			}
		}
		else
			transparency.rgb = 0xFF000000;

		if (ref_rays[index].id >= 0)
		{
			if (objs[ref_rays[index].id].texture >= 0)
				c = ft_texture_color(ref_rays[index], objs + ref_rays[index].id, textures + objs[ref_rays[index].id].texture);
			else
				c = objs[ref_rays[index].id].color;
			current = ft_color_bright(c, ambient);
			ft_light(&current, ref_rays[index], lights, objs + ref_rays[index].id, objs, textures, c);
		}
		else
			current.rgb = 0xFF000000;
		
		coeffs = ft_color_coeff(objs[ref_rays[index].id].reflect, objs[ref_rays[index].id].trans);

		colors[index] = ft_color_add(ft_color_add(reflection, coeffs.x,
												transparency, coeffs.y), 1,
												current, coeffs.z);
	}

	if (limit > 1)
	{
		reflection = colors[0];
		transparency = colors[1];
	}
	else
	{
		if (ref_rays[0].id >= 0)
		{
			if (objs[ref_rays[0].id].texture < 0)
				c = objs[ref_rays[0].id].color;
			else
				c = ft_texture_color(ref_rays[0], objs + ref_rays[0].id, textures + objs[ref_rays[0].id].texture);
			reflection = ft_color_bright(c, ambient);
			ft_light(&reflection, ref_rays[index * 2 + 2], lights, objs + ref_rays[index * 2 + 2].id, objs, textures, c);
		}
		else
			reflection.rgb = 0xFF000000;
		if (ref_rays[1].id >= 0)
		{
			if (objs[ref_rays[1].id].texture < 0)
				c = objs[ref_rays[1].id].color;
			else
				c = ft_texture_color(ref_rays[1], objs + ref_rays[1].id, textures + objs[ref_rays[1].id].texture);
			transparency = ft_color_bright(c, ambient);
			ft_light(&transparency, ref_rays[index * 2 + 3], lights, objs + ref_rays[index * 2 + 3].id, objs, textures, c);
		}
		else
			transparency.rgb = 0xFF000000;
	}
	coeffs = ft_color_coeff(objs[base_ray.id].reflect, objs[base_ray.id].trans);
	// img[id] = reflection;
	// if (objs[base_ray.id].type == ID_SPHERE)
	// 	printf("r: %f t: %f b: %f\n", coeffs.x, coeffs.y, coeffs.z);
	img[id] = ft_color_add(ft_color_add(reflection, coeffs.x,
										transparency, coeffs.y), 1,
										img[id], coeffs.z);
}