#include "./kernels/kernel.h"

void ft_get_small_pix_mat(const int *img, const int pos, const int width, t_color pix[3][3])
{
	pix[0][0].rgb = img[pos - width - 1];
	pix[0][1].rgb = img[pos - width];
	pix[0][2].rgb = img[pos - width + 1];
	pix[1][0].rgb = img[pos - 1];
	pix[1][1].rgb = img[pos];
	pix[1][2].rgb = img[pos + 1];
	pix[2][0].rgb = img[pos + width - 1];
	pix[2][1].rgb = img[pos + width];
	pix[2][2].rgb = img[pos + width + 1];
}

int	ft_secure_byte(const int byte, const int type)
{
	if (byte >= 256)
		return (255);
	else if (type == 0 && byte < 0)
		return (0);
	else if (type == 1 && byte < -255)
		return (-255);
	return (byte);
}

/*
** 	G(x) 3 x 3:
**  [-1][0][1]
**  [-2][0][2]
**  [-1][0][1]
*/

static void	init_kernel_x(int mat[3][3])
{
	mat[0][0] = -1;
	mat[0][1] = -2;
	mat[0][2] = -1;
	mat[1][0] = 0;
	mat[1][1] = 0;
	mat[1][2] = 0;
	mat[2][0] = 1;
	mat[2][1] = 2;
	mat[2][2] = 1;
}

/*
** 	G(y) 3 x 3:
**  [-1][-2][-1]
**  [ 0][ 0][ 0]
**  [ 1][ 2][ 1]
*/

static void	init_kernel_y(int mat[3][3])
{
	mat[0][0] = -1;
	mat[0][1] = 0;
	mat[0][2] = 1;
	mat[1][0] = -2;
	mat[1][1] = 0;
	mat[1][2] = 2;
	mat[2][0] = -1;
	mat[2][1] = 0;
	mat[2][2] = 1;
}

static int	apply_sobel(t_color pix[3][3], const int g_x[3][3], const int g_y[3][3]/*, float *dir*/)
{
	int		i;
	int		j;
	float	result[3];
	t_color	res;

	i = -1;
	result[0] = 0;
	result[1] = 0;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
		{
			result[0] += (float)pix[i][j].byte[0] * ((float)g_x[i][j]) / 4.0;
			result[1] += (float)pix[i][j].byte[0] * ((float)g_y[i][j]) / 4.0;
		}
	}
	//result[0] = ft_secure_byte(result[0], 1);
	//result[1] = ft_secure_byte(result[1], 1);
//	*dir = atan2(result[1], result[0]) * 180.0 / M_PI;
//	*dir = (*dir > 0) ? *dir : *dir  + 180.0;
	result[2] = sqrt(result[0] * result[0] + result[1] * result[1]);
	res.byte4.w = 0xFF;
	res.byte4.xyz = result[2];//ft_secure_byte(result[2], 1);
	if (res.byte4.x < 10)
		 return (0x00000000);
	return (0xFF000000);
}

__kernel void				ft_rt_sobel(const __private int			width,
										const __private int			height,
										__global t_color			*src,
										__global t_color			*dest)
{
	int			g_x[3][3];
	int			g_y[3][3];

	const __private int		id = get_global_id(0);

	t_color		pix[3][3];

	init_kernel_x(g_x);
	init_kernel_y(g_y);
	if (id % width == 0 || id % width == (width - 1)
			|| id <= width || id >= width * (height - 1))
			dest[id].rgb = 0xFF000000;
	else
	{
		ft_get_small_pix_mat(src, id, width, pix);
		dest[id].rgb = apply_sobel(pix, g_x, g_y);
	}
}
