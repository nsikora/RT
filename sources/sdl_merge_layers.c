/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_merge_layers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeigne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 18:29:04 by ppeigne           #+#    #+#             */
/*   Updated: 2018/08/20 18:29:05 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	ft_display_fps(t_env *env)
{
	char					*fps;

	fps = ft_itoa(env->param.fps);
	ft_ttf_render_txt_b_screen(env, fps, env->menu.white, env->menu.fps_rect);
	free(fps);
}

void		ft_sdl_merge_layers(t_env *env)
{
	SDL_FillRect(env->screen, NULL, 0xFF000000);
	SDL_BlitSurface(env->rt_param.lay_rt, NULL,
		env->screen, &env->menu.rt_rect);
	SDL_BlitSurface(env->preview_param.lay_rt, NULL,
		env->screen, &env->menu.preview_rect);
	ft_draw_ortho(env);
	SDL_BlitSurface(env->lay_menu, NULL, env->screen, NULL);
	if (env->menu.menu == 0)
		ft_display_fps(env);
	SDL_UpdateWindowSurface(env->win);
	env->param.merge_layers = 0;
}
