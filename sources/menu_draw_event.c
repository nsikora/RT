/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_draw_event.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbard <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 19:07:07 by jbard             #+#    #+#             */
/*   Updated: 2018/08/20 19:07:09 by jbard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_draw_event(t_env *env)
{
	int			i;
	SDL_Rect	rect;

	i = floor(env->param.mouse_pos_y / (float)env->param.height * 9.);
	if (i != env->menu.menu && i < 7 && env->menu.menu_quit)
	{
		rect = (SDL_Rect){env->menu.button_coor[i].x,
			env->menu.button_coor[i].y, 0, 0};
		SDL_BlitSurface(env->menu.highlight_square, NULL, env->lay_menu,
			&rect);
		env->menu.tmp_menu = (char)i;
	}
	env->menu.event = 0;
}
