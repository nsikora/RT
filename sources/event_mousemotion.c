/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_mousemotion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbard <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 18:47:10 by jbard             #+#    #+#             */
/*   Updated: 2018/08/20 18:47:11 by jbard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** ft_event_mousemotion:
**
** Give the coordinates of the cursor on the SDL window.
*/

void	ft_event_mousemotion(t_env *env)
{
	env->param.mouse_pos_x = env->event.motion.x;
	env->param.mouse_pos_y = env->event.motion.y;
	if (env->param.mouse_right_button)
	{
		env->param.x_gap += (env->param.tmp_x - env->param.mouse_pos_x);
		env->param.y_gap += (env->param.tmp_y - env->param.mouse_pos_y);
		env->param.change = 1;
		env->param.rot = 1;
		env->rt_param.compute = 1;
		env->preview_param.compute = 1;
	}
	if (env->menu.menu_coor[2] >= (size_t)env->param.mouse_pos_x
		&& env->menu.menu_coor[3] >= (size_t)env->param.mouse_pos_y)
	{
		env->param.menu_change = 1;
		env->menu.event = 1;
		env->menu.menu_quit = 1;
	}
	else if (env->menu.menu_quit == 1)
	{
		env->param.menu_change = 1;
		env->menu.event = 1;
		env->menu.menu_quit = 0;
	}
	SDL_FlushEvent(SDL_MOUSEMOTION);
}
