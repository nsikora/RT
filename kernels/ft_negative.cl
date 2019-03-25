#include "./kernels/kernel.h"

__kernel void				ft_rt_negative(__global t_color			*img)
{
	const __private int		id = get_global_id(0);

	img[id].byte4.w = 0xFF;
	img[id].byte4.x = 255 - img[id].byte4.x;
	img[id].byte4.y = 255 - img[id].byte4.y;
	img[id].byte4.z = 255 - img[id].byte4.z;
}
