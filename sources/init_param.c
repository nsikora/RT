/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_param.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeigne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 18:36:05 by ppeigne           #+#    #+#             */
/*   Updated: 2018/08/20 18:37:25 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	ft_init_sdl_color_part2(t_env *env, t_color c)
{
	c.urgb = 0xffe1e1e1;
	env->menu.grey = (SDL_Color){c.byte[BLUE], c.byte[GREEN], c.byte[RED],
		c.byte[ALPHA]};
}

static void	ft_init_sdl_color(t_env *env, t_color c)
{
	env->menu.white = (SDL_Color){c.byte[BLUE], c.byte[GREEN], c.byte[RED],
		c.byte[ALPHA]};
	c = (t_color)SOLARIZED_ACCENT_CYAN;
	env->menu.cyan = (SDL_Color){c.byte[BLUE], c.byte[GREEN], c.byte[RED],
		c.byte[ALPHA]};
	c = (t_color)SOLARIZED_ACCENT_ORANGE;
	env->menu.orange = (SDL_Color){c.byte[BLUE], c.byte[GREEN], c.byte[RED],
		c.byte[ALPHA]};
	c = (t_color)SOLARIZED_ACCENT_VIOLET;
	env->menu.violet = (SDL_Color){c.byte[BLUE], c.byte[GREEN], c.byte[RED],
		c.byte[ALPHA]};
	c = (t_color)SOLARIZED_ACCENT_RED;
	env->menu.red = (SDL_Color){c.byte[BLUE], c.byte[GREEN], c.byte[RED],
		c.byte[ALPHA]};
	c = (t_color)SOLARIZED_ACCENT_GREEN;
	env->menu.green = (SDL_Color){c.byte[BLUE], c.byte[GREEN], c.byte[RED],
		c.byte[ALPHA]};
	c = (t_color)SOLARIZED_ACCENT_BLUE;
	env->menu.blue = (SDL_Color){c.byte[BLUE], c.byte[GREEN], c.byte[RED],
		c.byte[ALPHA]};
	env->menu.filter_color[0] = env->menu.red;
	env->menu.filter_color[1] = env->menu.green;
	env->menu.filter_color[2] = env->menu.blue;
	ft_init_sdl_color_part2(env, c);
}

static void	ft_init_sdl_part2(t_env *env)
{
	SDL_Rect rect;

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
	SDL_FillRect(env->menu.menu_square, &rect, MENU_DARK_BLUE);
	ft_init_sdl_color(env, (t_color)WHITE);
}

void		ft_init_sdl(t_env *env)
{
	ft_sdl_init(env, env->param.width, env->param.height);
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
	ft_init_sdl_part2(env);
}

void		ft_init_rt_param(t_env *env)
{
	env->rt_param.width = env->menu.rt_rect.w;
	env->rt_param.height = env->menu.rt_rect.h;
	env->rt_param.scale = tan(ft_deg_to_rad(env->rt_param.fov * 0.5));
	env->preview_param.ambient = env->rt_param.ambient;
	env->preview_param.border = env->rt_param.border;
	env->preview_param.post = env->rt_param.post;
	env->preview_param.color = env->rt_param.color;
	env->preview_param.stereo = env->rt_param.stereo;
	env->preview_param.fov = env->rt_param.fov;
	env->preview_param.scale = env->rt_param.scale;
	env->preview_param.width = env->menu.preview_rect.w;
	env->preview_param.height = env->menu.preview_rect.h;
	ft_vec_copy(env->rt.cam_pos, env->menu.cam_pos);
	ft_quat_copy(env->rt.cam_rot, env->menu.cam_rot);
}
