#include "./kernels/kernel.h"

__kernel void				ft_cyan_filter(__global t_color			*img,
											const __private int	endian)
{
 	const __private int     id = get_global_id(0);
	__private t_color 		byte;
    byte.byte4.w = endian;

	byte.byte4.xyz = (img[id].byte[RED] * 0.4 + img[id].byte[GREEN] * 0.4
		+ img[id].byte[BLUE] * 0.4 < 255) ? img[id].byte[RED] * 0.4 +
		img[id].byte[GREEN] * 0.4	+ img[id].byte[BLUE] * 0.4 : 255;
/*
	byte.byte4.xyz = img[id].byte4[RED] * 0.3 + img[id].byte4[GREEN] * 0.3
		+ img[id].byte4[BLUE] * 0.3;*/
	img[id].byte4.w = endian;
   	img[id].byte4.xyz = 0;
	img[id].byte[2]	= byte.byte4.x;
	img[id].byte[1]	= byte.byte4.x;
	/*
	** why not img[id].byte4.yz = byte.byte4.x; ?
	*/
}
