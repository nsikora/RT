/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeigne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 18:51:36 by ppeigne           #+#    #+#             */
/*   Updated: 2018/08/20 18:51:40 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			ft_bresenham_init(const size_t *coor, int d[2],
										int s[2], int e[2])
{
	d[V_X] = abs((int)coor[2] - (int)coor[0]);
	d[V_Y] = abs((int)coor[3] - (int)coor[1]);
	s[V_X] = coor[0] < coor[2] ? 1 : -1;
	s[V_Y] = coor[1] < coor[3] ? 1 : -1;
	e[V_X] = (d[V_X] > d[V_Y] ? d[V_X] : -d[V_Y]) / 2;
}

void				ft_bresenham(const size_t *coor, int *img,
							const size_t width, const int color)
{
	size_t			p[2];
	int				d[2];
	int				s[2];
	int				e[2];

	ft_bresenham_init(coor, d, s, e);
	p[V_X] = coor[0];
	p[V_Y] = coor[1];
	while (1)
	{
		img[p[V_X] + p[V_Y] * width] = color;
		if (p[V_X] == coor[2] && p[V_Y] == coor[3])
			break ;
		if ((e[V_Y] = e[V_X]) > -d[V_X])
		{
			e[V_X] -= d[V_Y];
			p[V_X] += s[V_X];
		}
		if (e[V_Y] < d[V_Y])
		{
			e[V_X] += d[V_X];
			p[V_Y] += s[V_Y];
		}
	}
}
