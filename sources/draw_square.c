/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_square.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbard <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 19:05:09 by jbard             #+#    #+#             */
/*   Updated: 2018/08/20 19:05:10 by jbard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ft_draw_square(const size_t *coor, int *img,
			const size_t width, const int color)
{
	size_t i;
	size_t j;

	i = coor[0] - 1;
	while (++i < coor[2])
	{
		j = coor[1] - 1;
		while (++j < coor[3])
			img[width * j + i] = color;
	}
}
