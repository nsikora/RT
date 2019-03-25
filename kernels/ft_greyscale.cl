#include "./kernels/kernel.h"

__kernel void				ft_rt_greyscale(__global t_color			*img)
{
	const __private int		id = get_global_id(0);

	img[id].byte4.w = 0xFF;
	img[id].byte4.xyz = img[id].byte[RED] * 0.3
		+ img[id].byte[GREEN] * 0.59
		+ img[id].byte[BLUE] * 0.11;
}
