/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_angle_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbard <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 19:05:44 by jbard             #+#    #+#             */
/*   Updated: 2018/08/20 19:05:45 by jbard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void					ft_draw_upleft_angle(const size_t *coor, int *img,
						const size_t width, const int color)
{
	size_t				y;
	size_t				x;
	static const int	tab[] = {10, 7, 5, 4, 3, 2, 2, 1, 1, 1};
	int					size;

	size = -1;
	y = coor[1];
	while (++size < 10)
	{
		x = coor[0] + tab[size] + 1;
		while (--x > coor[0])
			img[width * y + x] = color;
		++y;
	}
}

void					ft_draw_downleft_angle(const size_t *coor, int *img,
						const size_t width, const int color)
{
	size_t				y;
	size_t				x;
	static const int	tab[] = {10, 7, 5, 4, 3, 2, 2, 1, 1, 1};
	int					size;

	size = 10;
	y = coor[1];
	while (--size >= 0)
	{
		x = coor[0] + tab[size] + 1;
		while (--x > coor[0])
			img[width * y + x] = color;
		++y;
	}
}

void					ft_draw_downright_angle(const size_t *coor, int *img,
						const size_t width, const int color)
{
	size_t				y;
	size_t				x;
	static const int	tab[] = {10, 7, 5, 4, 3, 2, 2, 1, 1, 1};
	int					size;

	size = 10;
	y = coor[1];
	while (--size >= 0)
	{
		x = coor[0] - tab[size] - 1;
		while (++x < coor[0])
			img[width * y + x] = color;
		++y;
	}
}

void					ft_draw_upright_angle(const size_t *coor, int *img,
						const size_t width, const int color)
{
	size_t				y;
	size_t				x;
	static const int	tab[] = {1, 1, 1, 2, 2, 3, 4, 5, 7, 10};
	int					size;

	size = 10;
	y = coor[1];
	while (--size >= 0)
	{
		x = coor[0] - tab[size] - 1;
		while (++x < coor[0])
			img[width * y + x] = color;
		++y;
	}
}

void					ft_draw_all_angles(t_env *env)
{
	ft_draw_upleft_angle((size_t[2]){env->menu.rt_rect.x - 1,
		env->menu.rt_rect.y + 5}, env->menu.lay_base->pixels, env->param.width,
		MENU_DARK_BLUE);
	ft_draw_upleft_angle((size_t[2]){env->menu.preview_rect.x + 4,
		env->menu.preview_rect.y}, env->menu.lay_base->pixels, env->param.width,
		MENU_DARK_BLUE);
	ft_draw_downleft_angle((size_t[2]){env->menu.preview_rect.x + 4,
		env->menu.info_coor[3] - 15}, env->menu.lay_base->pixels,
		env->param.width, MENU_DARK_BLUE);
	ft_draw_upright_angle((size_t[2]){env->param.width - 5,
		5}, env->menu.lay_base->pixels, env->param.width,
		MENU_DARK_BLUE);
	ft_draw_downright_angle((size_t[2]){env->param.width - 5,
		env->param.height - 15}, env->menu.lay_base->pixels, env->param.width,
		MENU_DARK_BLUE);
}
