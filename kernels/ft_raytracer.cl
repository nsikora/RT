#include "./kernels/kernel.h"
#include "./kernels/methods/ft_raycast.cl"
#include "./kernels/methods/ft_textures.cl"
#include "./kernels/methods/ft_perturbation.cl"

/*
	u = ϕ / 2π
	v = (π - θ) / π

	θ = atan(p.z / p.x)
	ϕ = acos(p.y / mag(p));
*/

__kernel void				ft_raytracer_base(const __private t_vec3	cam_pos,
												const __private float4		cam_rot,
												const __private int			width,
												const __private int			height,
												const __private t_dec		scale,
												const __constant t_obj		*objs,
												const __constant t_tex		*textures,
												__global t_color			*img,
												__global t_ray				*rays)
{
	const __private int		id = get_global_id(0);

	__private t_vec3		dir;
	__private t_vec3		tmp;
	__private t_ray			ray;
	__private t_color		c;

	dir.x = (2 * ((id % width) + 0.5) / (t_dec)width - 1) *
		(t_dec)width / (t_dec)height * scale;
	dir.y = (1 - 2 * ((id / width) + 0.5) / (t_dec)height) * scale;
	dir.z = -1;
	dir = fast_normalize(dir);

	tmp = cross(cam_rot.yzw, dir) * 2;
	dir += tmp * cam_rot.x + cross(cam_rot.yzw, tmp);

	c.rgb = 0xFF000000;

		// printf("t_obj: %lu\n", sizeof(t_obj));

	// < ---  RAYTRACING  --- >

	// Setup ray and cast it :
	ft_init_ray(&ray, cam_pos, dir);
	ft_raycast(objs, &ray, -1);
	if (ray.id >= 0) // Found something
	{
		// Compute normal + point in space :
		ft_compute_p_normal(&ray, objs + ray.id, false);
		if (objs[ray.id].texture_norm >= 0)
			ft_texture_norm(&ray, objs + ray.id, textures + objs[ray.id].texture_norm);
		else if (objs[ray.id].texture_norm == -2)
			ft_apply_sin_to_norm(&ray);
		else if (objs[ray.id].texture_norm == -3)
			ft_apply_noise_to_norm(&ray, objs + ray.id);
		// if (objs[ray.id].texture >= 0)
		// 	c = ft_texture_color(ray, objs[ray.id], textures[objs[ray.id].texture]);
		// else
		// 	c = objs[ray.id].color;
		//c.rgb = ft_2D_checkerboard(ray.p, objs[ray.id].pos);
		c = objs[ray.id].color;
	}
	rays[id] = ray;
	img[id] = c;
}
