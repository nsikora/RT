/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_fullscreen.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbard <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 18:45:13 by jbard             #+#    #+#             */
/*   Updated: 2018/08/20 18:45:14 by jbard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** ft_event_keyup:
**
** Create an event when a key is released.
*/

void	ft_event_fullscreen(t_env *env)
{
	if (env->param.fullscreen)
	{
		SDL_SetWindowFullscreen(env->win, 0);
		env->param.fullscreen = 0;
	}
	else
	{
		SDL_SetWindowFullscreen(env->win, SDL_WINDOW_FULLSCREEN_DESKTOP);
		env->param.fullscreen = 1;
	}
}
