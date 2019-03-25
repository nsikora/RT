/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_gradient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbard <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 19:06:14 by jbard             #+#    #+#             */
/*   Updated: 2018/08/20 19:06:18 by jbard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				ft_draw_left_gradient(const size_t *coor, int *img,
					const size_t width)
{
	t_color			gradient;
	size_t			i;
	size_t			j;

	i = coor[0] - 1;
	gradient.rgb = 0;
	while (++i < coor[2])
	{
		gradient.byte[ALPHA] = (unsigned char)
			(((coor[2] - i) / (float)(coor[2] - coor[0])) * 70.);
		j = coor[1] - 1;
		while (++j < coor[3])
			img[width * j + i] += gradient.rgb;
	}
}

void				ft_draw_right_gradient(const size_t *coor, int *img,
					const size_t width)
{
	t_color			gradient;
	size_t			i;
	size_t			j;

	i = coor[0] - 1;
	gradient.rgb = 0;
	while (++i < coor[2])
	{
		gradient.byte[ALPHA] = (unsigned char)
			(((i - coor[0]) / (float)(coor[2] - coor[0])) * 70.);
		j = coor[1] - 1;
		while (++j < coor[3])
			img[width * j + i] += gradient.rgb;
	}
}

void				ft_draw_down_gradient(const size_t *coor, int *img,
					const size_t width)
{
	t_color			gradient;
	size_t			i;
	size_t			j;

	i = coor[1] - 1;
	gradient.rgb = 0;
	while (++i < coor[3])
	{
		gradient.byte[ALPHA] = (unsigned char)
			(((i - coor[1]) / (float)(coor[3] - coor[1])) * 70.);
		j = coor[0] - 1;
		while (++j < coor[2])
			img[width * i + j] += gradient.rgb;
	}
}

void				ft_draw_up_gradient(const size_t *coor, int *img,
					const size_t width)
{
	t_color			gradient;
	size_t			i;
	size_t			j;

	i = coor[1] - 1;
	gradient.rgb = 0;
	while (++i < coor[3])
	{
		gradient.byte[ALPHA] = (unsigned char)
			(((coor[3] - i) / (float)(coor[3] - coor[1])) * 70.);
		j = coor[0] - 1;
		while (++j < coor[2])
			img[width * i + j] += gradient.rgb;
	}
}

void				ft_draw_all_gradients(t_env *env)
{
	ft_draw_left_gradient((size_t[4]){env->menu.rt_rect.x, 0,
		env->menu.rt_rect.x + 10, env->param.height},
		env->menu.lay_base->pixels, env->param.width);
	ft_draw_right_gradient((size_t[4]){env->param.width - 15, 0,
		env->param.width - 5, env->param.height},
		env->menu.lay_base->pixels, env->param.width);
	ft_draw_down_gradient((size_t[4]){env->menu.rt_rect.x,
		env->param.height - 15, env->param.width, env->param.height - 5},
		env->menu.lay_base->pixels, env->param.width);
	ft_draw_up_gradient((size_t[4]){env->menu.rt_rect.x, 5,
		env->param.width, 15},
		env->menu.lay_base->pixels, env->param.width);
}
