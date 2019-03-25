#include "./kernels/kernel.h"

int check_vertical(__global t_color *img, const int pos);
int check_horizontal(__global t_color *img, const int pos, const int width);
int check_diagonal1(__global t_color *img, const int pos, const int width);
int	check_diagonal2(__global t_color *img, const int pos, const int width);

int 						check_vertical(__global t_color *img,
											const int pos)
{
	t_color a;

	a.byte[0] = ((t_color)(img)[pos-1]).byte[0];
	a.byte[1] = ((t_color)(img)[pos]).byte[0];
	a.byte[2] = ((t_color)(img)[pos +1]).byte[0];
	if (a.byte[1] > a.byte[0] && a.byte[1] > a.byte[2])
		//return (img[pos]);
//		return (0xFF000000);
//		printf("V\n");
		return (0xFFFFFFFF);
	return (0x00000000);
}

int							check_horizontal(__global t_color *img,
											const int pos,
											const int width)
{
	t_color a;
	
	a.byte[0] = ((t_color)(img)[pos - width]).byte[0];
	a.byte[1] = ((t_color)(img)[pos]).byte[0];
	a.byte[2] = ((t_color)(img)[pos + width]).byte[0];
	if (a.byte[1] > a.byte[0] && a.byte[1] > a.byte[2])
		return (0xFFFFFFFF);
	return (0x00000000);
}

int 						check_diagonal1(__global t_color *img,
											const int pos,
											const int width)
{
	t_color a;

	a.byte[0] = ((t_color)(img)[pos - width - 1]).byte[0];
	a.byte[1] = ((t_color)(img)[pos]).byte[0];
	a.byte[2] = ((t_color)(img)[pos + width + 1]).byte[0];
	if (a.byte[1] > a.byte[0] && a.byte[1] > a.byte[2])
		return (0xFFFFFFFF);
	return (0x00000000);
}

int 						check_diagonal2(__global t_color *img,
											const int pos,
											const int width)
{
	t_color a;

	a.byte[0] = ((t_color)(img)[pos - width + 1]).byte[0];
	a.byte[1] = ((t_color)(img)[pos]).byte[0];
	a.byte[2] = ((t_color)(img)[pos + width - 1]).byte[0];
	if (a.byte[1] > a.byte[0] && a.byte[1] > a.byte[2])
		return (0xFFFFFFFF);
	return (0x00000000);
}

__kernel void				ft_rt_canny(const __private int	width,
										const __private int height,
										__global t_color	*img,
										__global float		*dir)
{
	const __private int     id = get_global_id(0);

	if (id % width == 0 || id % width == (width - 1)
			|| id <= width || id >= width * (height - 1))
		img[id].rgb = 0xFF000000;
    else
	{
		if (dir[id] >= 67.5 && dir[id] < 112.5)
			img[id].rgb = check_vertical(img, id);
		else if ((dir[id] >= 0  && dir[id] < 22.5)
				|| (dir[id] >= 157.5 && dir[id] < 180))
			img[id].rgb = check_horizontal(img, id, width);
		else if (dir[id] >= 22.5 && dir[id] < 67.5)
			img[id].rgb = check_diagonal1(img, id, width);
		else if (dir[id] >= 112.5 && dir[id] < 157.5)
			img[id].rgb = check_diagonal2(img, id, width);
		else 
			img[id].rgb = 0x00000000;
	}
}
