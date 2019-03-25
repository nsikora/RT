/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_angle_out.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeigne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 18:55:01 by ppeigne           #+#    #+#             */
/*   Updated: 2018/08/20 18:55:02 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_draw_upleft_angle_out(const size_t *coor, int *img,
			const size_t width, const int color)
{
	size_t				y;
	size_t				x;
	static const int	tab[] = {7, 5, 4, 3, 2, 2, 1, 1, 1};
	int					size;

	size = -1;
	y = coor[1] + 1;
	while (++size < 9)
	{
		x = coor[0] + tab[size] - 1;
		while (++x < coor[0] + 13 - size)
			img[width * y + x] = color;
		++y;
	}
}
