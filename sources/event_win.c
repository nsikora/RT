/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_win.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbard <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 18:47:47 by jbard             #+#    #+#             */
/*   Updated: 2018/08/20 18:47:49 by jbard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** ft_event_win:
**
** Create an event when a key is released.
*/

void			ft_event_win(t_env *env)
{
	if (env->event.window.event == SDL_WINDOWEVENT_RESIZED)
		ft_update_win_specs(env);
}
