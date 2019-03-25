/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_win_update_specs.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbard <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 18:48:24 by jbard             #+#    #+#             */
/*   Updated: 2018/08/20 18:48:26 by jbard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** ft_event_win:
**
** Create an event when a key is released.
*/

static void		ft_free_sdl(t_env *env)
{
	ft_sdl_free_surface(&env->rt_param.lay_rt);
	ft_sdl_free_surface(&env->rt_param.lay_stereo);
	ft_sdl_free_surface(&env->rt_param.lay_border);
	ft_sdl_free_surface(&env->rt_param.lay_post);
	ft_sdl_free_surface(&env->preview_param.lay_rt);
	ft_sdl_free_surface(&env->preview_param.lay_stereo);
	ft_sdl_free_surface(&env->preview_param.lay_border);
	ft_sdl_free_surface(&env->preview_param.lay_post);
	ft_sdl_free_surface(&env->lay_menu);
	ft_sdl_free_surface(&env->menu.lay_base);
	ft_sdl_free_surface(&env->menu.lay_event);
	ft_sdl_free_surface(&env->menu.lay_logo);
	ft_sdl_free_surface(&env->menu.select_square);
	ft_sdl_free_surface(&env->menu.highlight_square);
	ft_sdl_free_surface(&env->menu.highlight_option);
	ft_sdl_free_surface(&env->menu.select_option);
	ft_sdl_free_surface(&env->menu.menu_square);
}

static void		ft_update_sdl_part2(t_env *env)
{
	SDL_Rect rect;

	env->screen = SDL_GetWindowSurface(env->win);
	ft_menu_create_surf(&env->menu.highlight_square, env->menu.menu_coor[2],
		env->menu.button_coor[0].h, HIGHLIGHT_BLUE);
	ft_menu_create_surf(&env->menu.select_square, env->menu.menu_coor[2],
		env->menu.button_coor[0].h, MENU_DARK_BLUE);
	ft_menu_create_surf(&env->menu.highlight_option, env->menu.sub_menu_coor[2]
		- env->menu.sub_menu_coor[0], env->menu.button_coor[0].h,
		HIGHLIGHT_BLUE);
	ft_draw_angle_option(env->menu.highlight_option);
	ft_menu_create_surf(&env->menu.select_option, env->menu.sub_menu_coor[2] -
		env->menu.sub_menu_coor[0], env->menu.button_coor[0].h,
		MENU_LIGHT_BLUE);
	ft_draw_angle_option(env->menu.select_option);
	ft_menu_create_surf(&env->menu.menu_square, env->menu.sub_menu_coor[2],
		env->menu.menu_coor[3], MENU_LIGHT_BLUE);
	rect = (SDL_Rect){env->menu.menu_coor[2], 0, env->menu.sub_menu_coor[2],
		env->menu.sub_menu_coor[3]};
	ft_create_lay_logo(env);
	SDL_FillRect(env->menu.menu_square, &rect, MENU_DARK_BLUE);
}

static void		ft_update_sdl(t_env *env)
{
	ft_sdl_create_surface(&env->rt_param.lay_rt,
		env->menu.rt_rect.w, env->menu.rt_rect.h);
	ft_sdl_create_surface(&env->rt_param.lay_stereo,
		env->menu.rt_rect.w, env->menu.rt_rect.h);
	ft_sdl_create_surface(&env->rt_param.lay_border,
		env->menu.rt_rect.w, env->menu.rt_rect.h);
	ft_sdl_create_surface(&env->rt_param.lay_post,
		env->menu.rt_rect.w, env->menu.rt_rect.h);
	ft_sdl_create_surface(&env->preview_param.lay_rt,
		env->menu.preview_rect.w, env->menu.preview_rect.h);
	ft_sdl_create_surface(&env->preview_param.lay_stereo,
		env->menu.preview_rect.w, env->menu.preview_rect.h);
	ft_sdl_create_surface(&env->preview_param.lay_border,
		env->menu.preview_rect.w, env->menu.preview_rect.h);
	ft_sdl_create_surface(&env->preview_param.lay_post,
		env->menu.preview_rect.w, env->menu.preview_rect.h);
	ft_sdl_create_surface(&env->lay_menu, env->param.width, env->param.height);
	ft_sdl_create_surface(&env->menu.lay_base, env->param.width,
		env->param.height);
	ft_sdl_create_surface(&env->menu.lay_event, env->menu.menu_coor[2],
		env->menu.menu_coor[3]);
	ft_sdl_create_surface(&env->menu.lay_logo, env->menu.menu_coor[2],
		env->menu.menu_coor[3]);
	ft_update_sdl_part2(env);
}

static void		ft_update_rt_param(t_env *env)
{
	env->rt_param.width = env->menu.rt_rect.w;
	env->rt_param.height = env->menu.rt_rect.h;
	env->preview_param.width = env->menu.preview_rect.w;
	env->preview_param.height = env->menu.preview_rect.h;
}

void			ft_update_win_specs(t_env *env)
{
	SDL_DisplayMode mode;

	SDL_GetWindowSize(env->win, &env->param.width, &env->param.height);
	SDL_GetWindowDisplayMode(env->win, &mode);
	if (env->param.fullscreen != 1 && mode.w == env->param.width
		&& mode.h == env->param.height)
	{
		SDL_SetWindowFullscreen(env->win, SDL_WINDOW_FULLSCREEN_DESKTOP);
		env->param.fullscreen = 1;
	}
	ft_ttf_close_font(&env->pt_mono);
	ft_compute_menu_pos(env);
	ft_update_all_sliders(&env->menu);
	ft_free_sdl(env);
	ft_update_rt_param(env);
	ft_update_sdl(env);
	ft_display_load(env);
	ft_release_all(&env->rt_param);
	ft_release_all(&env->preview_param);
	ft_build_obj_rt(env, &env->rt_param);
	ft_build_obj_rt(env, &env->preview_param);
	env->param.change = 1;
	env->param.menu_change = 1;
	env->rt_param.compute = 1;
	env->preview_param.compute = 1;
}
