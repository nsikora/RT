/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_angle_option.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbard <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 19:04:44 by jbard             #+#    #+#             */
/*   Updated: 2018/08/20 19:04:46 by jbard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_draw_angle_option(SDL_Surface *surf)
{
	int i;

	i = -1;
	while (++i < surf->h)
		((int *)(surf->pixels))[i * surf->w] = MENU_DARK_BLUE;
	ft_draw_upleft_angle((size_t[2]){0, 0}, surf->pixels, surf->w,
		MENU_DARK_BLUE);
	ft_draw_downleft_angle((size_t[2]){0, surf->h - 10}, surf->pixels, surf->w,
		MENU_DARK_BLUE);
	ft_draw_upright_angle((size_t[2]){surf->w, 0}, surf->pixels, surf->w,
		MENU_DARK_BLUE);
	ft_draw_downright_angle((size_t[2]){surf->w, surf->h - 10}, surf->pixels,
		surf->w, MENU_DARK_BLUE);
}
