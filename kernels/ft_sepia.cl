#include "./kernels/kernel.h"

__kernel void				ft_rt_sepia(__global t_color			*img)
{
	const __private int		id = get_global_id(0);
	__private t_color col = img[id];
	
	col.byte4.w = 0xFF;
	col.byte4.x = (float)img[id].byte4.x * 0.393
		+ (float)img[id].byte4.y * 0.769
		+ (float)img[id].byte4.z * 0.189;
//	if (col.byte4.x > 255)
//		col.byte4.x = 255;

	col.byte4.y = (float)img[id].byte4.x * 0.349
		+ (float)img[id].byte4.y * 0.686
		+ (float)img[id].byte4.z * 0.168;	
//	if (col.byte4.y > 255)
//		col.byte4.y = 255;	
	col.byte4.z = (float)img[id].byte4.x * 0.272
		+ (float)img[id].byte4.y * 0.534 
		+ (float)img[id].byte4.z * 0.131;
//	if (col.byte4.z > 255)
//		col.byte4.z = 255;
	
	/*	
	col.byte4.w = 0xFF;
	col.byte[RED] = (float)img[id].byte4[RED] * 0.393
		+ (float)img[id].byte4[GREEN] * 0.769
		+ (float)img[id].byte4[BLUE] * 0.189;
	if (col.byte[RED] > 255)
		col.byte[RED] = 255;
	col.byte[GREEN] = (float)img[id].byte4[RED] * 0.349
		+ (float)img[id].byte4[GREEN] * 0.686
		+ (float)img[id].byte4[BLUE] * 0.168;	
	if (col.byte[GREEN] > 255)
		col.byte[GREEN] = 255;
	col.byte[BLUE] = (float)img[id].byte4[RED] * 0.272
		+ (float)img[id].byte4[GREEN] * 0.534 
		+ (float)img[id].byte4[BLUE] * 0.131;
	if (col.byte[BLUE] > 255)
		col.byte[BLUE] = 255;
*/	img[id] = col;

}
