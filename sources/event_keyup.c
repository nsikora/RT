/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_keyup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbard <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 18:46:00 by jbard             #+#    #+#             */
/*   Updated: 2018/08/20 18:46:06 by jbard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** ft_event_keyup:
**
** Create an event when a key is released.
*/

static void		event_sdlk_r(t_env *env)
{
	ft_vec_copy(env->menu.cam_pos, env->rt.cam_pos);
	ft_quat_copy(env->menu.cam_rot, env->rt.cam_rot);
	env->param.x_gap = 0;
	env->param.y_gap = 0;
	env->param.change = 1;
	env->rt_param.compute = 1;
	env->preview_param.compute = 1;
}

static void		event_sdlk_page(t_env *env, int dir)
{
	if (dir < 0 && env->preview_param.r_limit > 0)
		env->preview_param.r_limit -= 1;
	else if (dir > 0 && env->preview_param.r_limit < 7)
		env->preview_param.r_limit += 1;
	else
		return ;
	if (env->menu.limit_val)
		free(env->menu.limit_val);
	env->menu.limit_val = ft_itoa(env->preview_param.r_limit);
	env->param.change = 1;
	env->preview_param.compute = 1;
	env->param.menu_change = 1;
	env->menu.redraw = 1;
}

static void		ft_cancel_change(t_env *env)
{
	ft_copy_param_content(&env->rt_param, &env->preview_param);
	env->param.menu_change = 1;
	env->menu.redraw = 1;
	env->param.change = 1;
}

void			ft_event_keyup(t_env *env)
{
	if (env->event.key.keysym.sym == SDLK_KP_PLUS)
		env->param.step += 0.5;
	else if (env->event.key.keysym.sym == SDLK_KP_MINUS)
		ft_event_sdl_kp_minus(env);
	else if (env->event.key.keysym.sym == SDLK_r)
		event_sdlk_r(env);
	else if (env->event.key.keysym.sym == SDLK_t)
		ft_event_screenshot(env);
	else if (env->event.key.keysym.sym == SDLK_f)
		ft_event_fullscreen(env);
	else if (env->event.key.keysym.sym == SDLK_u)
		ft_event_sdlk_u(env);
	else if (env->event.key.keysym.sym == SDLK_PAGEDOWN)
		event_sdlk_page(env, -1);
	else if (env->event.key.keysym.sym == SDLK_PAGEUP)
		event_sdlk_page(env, 1);
	else if (env->event.key.keysym.sym == SDLK_BACKSPACE)
		ft_cancel_change(env);
	else if (env->event.key.keysym.sym == SDLK_RETURN)
	{
		ft_copy_param_content(&env->preview_param, &env->rt_param);
		env->param.change = 1;
	}
}
