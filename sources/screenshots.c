/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshots.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeigne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 13:16:16 by ppeigne           #+#    #+#             */
/*   Updated: 2018/08/17 16:12:47 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	ft_dib_header(const int fd, const int height, const int width)
{
	int	dib_header[10];

	dib_header[0] = 0x00000028;
	dib_header[1] = width;
	dib_header[2] = height;
	dib_header[3] = 0x00180001;
	dib_header[4] = 0;
	dib_header[5] = 0x0015F900;
	dib_header[6] = 0x00000B13;
	dib_header[7] = 0x00000B13;
	dib_header[8] = 0;
	dib_header[9] = 0;
	write(fd, (void*)dib_header, sizeof(int) * 10);
}

static void	ft_bmp_header(const int fd, const int height, const int width)
{
	int size;
	int bmp_header[3];

	size = 3 * height * width + 54;
	bmp_header[0] = size;
	bmp_header[1] = 0;
	bmp_header[2] = 0x00000036;
	ft_putstr_fd("BM", fd);
	write(fd, (void*)bmp_header, sizeof(int) * 3);
	ft_dib_header(fd, height, width);
}

static void	ft_surface_cpy(t_env *env, t_bmp *img, int x)
{
	int y;
	int i;
	int j;

	i = env->rt_param.height * env->rt_param.width - 1;
	j = 0;
	y = 0;
	while (y < env->rt_param.height)
	{
		x = 0;
		j = (y + 1) * env->rt_param.width - 1;
		while (x < env->rt_param.width)
		{
			img[j][0] = ((t_color *)
			(env->rt_param.lay_rt->pixels))[i].byte[RED];
			img[j][1] = ((t_color *)
			(env->rt_param.lay_rt->pixels))[i].byte[GREEN];
			img[j][2] = ((t_color *)
			(env->rt_param.lay_rt->pixels))[i].byte[BLUE];
			i--;
			j--;
			x++;
		}
		y++;
	}
}

void		ft_screenshot(t_env *env)
{
	int		fd;
	t_bmp	*img;
	size_t	size;

	size = 3 * env->rt_param.height * env->rt_param.width;
	img = (t_bmp *)malloc(sizeof(char)
		* size);
	if ((fd = open("screenshot.bmp", O_WRONLY | O_CREAT | O_TRUNC,
					S_IWUSR | S_IRUSR)) == -1)
		ft_putendl("Error opening file");
	ft_bmp_header(fd, env->rt_param.height, env->rt_param.width);
	ft_surface_cpy(env, img, 0);
	write(fd, (void*)img, size);
	free(img);
	if (close(fd) == -1)
		ft_putendl("Error closing file");
}
