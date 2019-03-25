#include "./kernels/kernel.h"
#include "./kernels/methods/ft_raycast.cl"

__kernel void				ft_selector(const __private t_vec3	cam_pos,
										const __private float4		cam_rot,
										const __private int			width,
										const __private int			height,
										const __private t_dec		scale,
										const __constant t_obj		*objs,
										const __private int			x,
										const __private int			y,
										__global int		*id)
{
	__private t_vec3		dir;
	__private t_vec3		tmp;
	__private t_ray			ray;

	dir.x = (2 * (x + 0.5) / (t_dec)width - 1) *
		(t_dec)width / (t_dec)height * scale;
	dir.y = (1 - 2 * (y + 0.5) / (t_dec)height) * scale;
	dir.z = -1;
	dir = fast_normalize(dir);

	tmp = cross(cam_rot.yzw, dir) * 2;
	dir += tmp * cam_rot.x + cross(cam_rot.yzw, tmp);

	ft_init_ray(&ray, cam_pos, dir);
	ft_raycast(objs, &ray, -1);
	*id = -1;
	if (ray.id >= 0)
		*id = ray.id;
}