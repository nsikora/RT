#include "./kernels/kernel.h"
#include "./kernels/methods/ft_raycast.cl"
#include "./kernels/methods/ft_color.cl"
#include "./kernels/methods/ft_lights.cl"

__kernel void				ft_raytracer_light_toon(const __private t_dec	ambient,
													const __constant t_obj 	*objs,
													const __constant t_light	*lights,
													const __constant t_tex      *textures,
													__global t_color			*img,
													__global t_ray				*rays)
{
	const __private int		id = get_global_id(0);
	const __private t_ray	ray = rays[id];
	__private t_color		c;
	__private t_color		color;

	if (ray.id >= 0)
	{
		if (objs[ray.id].texture >= 0)
			color = ft_texture_color(ray, objs + ray.id, textures + objs[ray.id].texture);
		else if (objs[ray.id].texture == -2)
			color.rgb = ft_2D_checkerboard(&ray, objs + ray.id);
		else
			color = img[id];
		c = ft_color_bright(color, ambient);
		ft_light_toon(&c, ray, lights, objs, color);
		img[id] = c;
	}
}
