#include "./kernels/kernel.h"

int apply_big_kernel(t_color pix[5][5], const int kern[5][5])
{
	int i;
	int j;
	t_color res;
	float r = 0;
	float g = 0;
	float b = 0;
	i = 0;
	res.rgb = 0xFF000000;
	while (i < 5)
	{
		j = 0;
		while (j < 5)
		{
			r += ((float)kern[i][j] * (float)pix[i][j].byte[0] / 273.0);
			g += ((float)kern[i][j] * (float)pix[i][j].byte[1] / 273.0);
			b += ((float)kern[i][j] * (float)pix[i][j].byte[2] / 273.0);
			j++;
		}
		i++;
	}
	res.byte[0] = r;
	res.byte[1] = g;
	res.byte[2] = b;
	return (res.rgb);
}

void ft_get_big_pix_mat(const int *img, const int pos, const int width, t_color pix[5][5])
{
	pix[0][0].rgb = img[pos - (width * 2) - 2];
	pix[0][1].rgb = img[pos - (width * 2) - 1];
	pix[0][2].rgb = img[pos - (width * 2)];
	pix[0][3].rgb = img[pos - (width * 2) + 1];
	pix[0][4].rgb = img[pos - (width * 2) + 2];
	pix[1][0].rgb = img[pos - width - 2];
	pix[1][1].rgb = img[pos - width - 1];
	pix[1][2].rgb = img[pos - width];
	pix[1][3].rgb = img[pos - width + 1];
	pix[1][4].rgb = img[pos - width + 2];
	pix[2][0].rgb = img[pos - 2];
	pix[2][1].rgb = img[pos - 1];
	pix[2][2].rgb = img[pos];
	pix[2][3].rgb = img[pos + 1];
	pix[2][4].rgb = img[pos + 2];
	pix[3][0].rgb = img[pos + width - 2];
	pix[3][1].rgb = img[pos + width - 1];
	pix[3][2].rgb = img[pos + width];
	pix[3][3].rgb = img[pos + width + 1];
	pix[3][4].rgb = img[pos + width + 2];
	pix[4][0].rgb = img[pos + (width * 2) - 2];
	pix[4][1].rgb = img[pos + (width * 2) - 1];
	pix[4][2].rgb = img[pos + (width * 2)];
	pix[4][3].rgb = img[pos + (width * 2) + 1];
	pix[4][4].rgb = img[pos + (width * 2) + 2];
}

/*
 ** GAUSSIAN KERNEL 5x5:
 ** 	[1][ 4][ 7][4] [1]
 ** 	[4][16][26][16][4]
 ** 	[7][26][41][26][7]
 **		[4][16][26][16][4]
 **		[1][ 4][ 7][ 4][1]
 */

void ft_init_big_gaussian(int mat[5][5])
{
	mat[0][0] = 1;
	mat[0][1] = 4;
	mat[0][2] = 7;
	mat[0][3] = 4;
	mat[0][4] = 1;
	mat[1][0] = 4;
	mat[1][1] = 16;
	mat[1][2] = 26;
	mat[1][3] = 16;
	mat[1][4] = 4;
	mat[2][0] = 7;
	mat[2][1] = 26;
	mat[2][2] = 41;
	mat[2][3] = 26;
	mat[2][4] = 7;
	mat[3][0] = 4;
	mat[3][1] = 16;
	mat[3][2] = 26;
	mat[3][3] = 16;
	mat[3][4] = 4;
	mat[4][0] = 1;
	mat[4][1] = 4;
	mat[4][2] = 7;
	mat[4][3] = 4;
	mat[4][4] = 1;
}

__kernel void				ft_rt_antialiasing(const __private int			width,
												const __private int			height,
												__global t_color			*src,
												__global t_color			*edges,
												__global t_color			*img)
{
	const __private int		id = get_global_id(0);

	int			blur[5][5];
	t_color		pix[5][5];

	if (id > width * 2 
			&& id < width * (height - 2) 
			&&id % width != 0 && id % width != 1
			&& id % width != (width - 1)
			&& id % width != (width - 2) 
			&& edges[id].rgb == 0xFFFFFFFF) 
	{
		ft_init_big_gaussian(blur);
		ft_get_big_pix_mat(src, id, width, pix);
		img[id].rgb = apply_big_kernel(pix, blur);
	}
	else 
		img[id].rgb = src[id].rgb;
}
