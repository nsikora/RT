/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_keydown.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbard <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 18:45:38 by jbard             #+#    #+#             */
/*   Updated: 2018/08/20 18:46:23 by jbard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** ft_event_keydown:
**
** Repeat an event while a key is pressed
** and not interupt by another key.
*/

void		ft_event_keydown(t_env *env)
{
	if (env->event.key.keysym.sym == SDLK_ESCAPE)
		env->param.quit = 0;
}
