/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_screenshot.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbard <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 18:47:22 by jbard             #+#    #+#             */
/*   Updated: 2018/08/20 18:47:24 by jbard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** ft_event_keyup:
**
** Create an event when a key is released.
*/

void	ft_event_screenshot(t_env *env)
{
	if (!env->param.fullscreen)
	{
		ft_event_fullscreen(env);
		ft_update_win_specs(env);
		env->rt_param.lay_dest = env->rt_param.lay_rt;
		ft_compute_rt(env, &env->rt_param);
		ft_screenshot(env);
		ft_event_fullscreen(env);
	}
	else
		ft_screenshot(env);
}
