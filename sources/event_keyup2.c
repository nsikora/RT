/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_keyup2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbard <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 18:46:45 by jbard             #+#    #+#             */
/*   Updated: 2018/08/20 18:46:47 by jbard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_event_sdlk_u(t_env *env)
{
	if (env->menu.selected_obj >= 0)
	{
		env->rt.objs[env->menu.selected_obj].color = env->menu.last_color;
		env->rt.objs[env->menu.selected_obj].texture = env->menu.last_tex;
		env->menu.selected_obj = -1;
		ft_rebuild_objs(env);
		env->preview_param.compute = 1;
		env->param.menu_change = 1;
		env->param.change = 1;
		env->rt_param.compute = 1;
		env->preview_param.compute = 1;
	}
}

void	ft_event_sdl_kp_minus(t_env *env)
{
	if (env->param.step > 0.5)
		env->param.step -= 0.5;
	else
		ft_putendl("Error: step is already at is minimum (= 0.5) value.");
}
