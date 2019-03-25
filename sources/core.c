/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbard <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 19:05:23 by jbard             #+#    #+#             */
/*   Updated: 2018/08/20 19:05:26 by jbard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	ft_rot_cam(t_env *env)
{
	t_quat	tmp_quat;
	t_quat	tmp_inv;
	t_quat	tmp_quat2;
	t_vec	vec_dir;

	ft_vec_to_quat((t_vec){1, 0, 0},
		env->param.y_gap / (float)HEIGHT * 360.0, tmp_quat);
	ft_vec_to_quat((t_vec){1, 0, 0},
		-env->param.y_gap / (float)HEIGHT * 360.0, tmp_inv);
	ft_quat_vec_mult(tmp_inv, (t_vec){0, 1, 0}, vec_dir);
	ft_normalize(vec_dir, vec_dir);
	ft_vec_to_quat(vec_dir,
		env->param.x_gap / (float)WIDTH * 360.0, tmp_quat2);
	ft_quat_mult(tmp_quat2, tmp_quat, env->rt.cam_rot);
	env->param.rot = 0;
}

static void	init_rt(t_env *env)
{
	if (env->param.rot)
		ft_rot_cam(env);
	if (env->rt_param.compute)
	{
		env->rt_param.lay_dest = env->rt_param.lay_rt;
		ft_compute_rt(env, &env->rt_param);
		env->rt_param.compute = 0;
	}
	if (env->preview_param.compute)
	{
		env->preview_param.lay_dest = env->preview_param.lay_rt;
		ft_compute_rt(env, &env->preview_param);
		env->preview_param.compute = 0;
	}
	env->param.merge_layers = 1;
	env->param.change = 0;
}

/*
** ft_core:
*/

static void	ft_handle_changes(t_env *env)
{
	ft_event_get_changes(env);
	if (env->param.change)
		init_rt(env);
	if (env->param.menu_change)
	{
		if (env->menu.redraw)
			ft_draw_menu(env);
		SDL_FillRect(env->lay_menu, NULL, 0);
		SDL_BlitSurface(env->menu.lay_base, NULL, env->lay_menu, NULL);
		if (env->menu.event)
			ft_draw_event(env);
		SDL_BlitSurface(env->menu.lay_logo, NULL, env->lay_menu, NULL);
		env->param.merge_layers = 1;
		env->param.menu_change = 0;
	}
	if (env->param.merge_layers)
		ft_sdl_merge_layers(env);
}

void		ft_core(t_env *env)
{
	while (env->param.quit)
	{
		while (SDL_PollEvent(&env->event))
		{
			if (env->event.type == SDL_QUIT)
				env->param.quit = 0;
			else if (env->event.type == SDL_MOUSEMOTION)
				ft_event_mousemotion(env);
			else if (env->event.type == SDL_KEYDOWN)
				ft_event_keydown(env);
			else if (env->event.type == SDL_KEYUP)
				ft_event_keyup(env);
			else if (env->event.type == SDL_MOUSEBUTTONUP)
				ft_event_buttonup(env);
			else if (env->event.type == SDL_WINDOWEVENT)
				ft_event_win(env);
			else if (env->event.type == SDL_MOUSEWHEEL)
				ft_event_scroll(env);
		}
		if (ft_event_fps_limiter(env))
			ft_handle_changes(env);
	}
}
