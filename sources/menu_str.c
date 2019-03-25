/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtheo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 08:36:43 by dtheo             #+#    #+#             */
/*   Updated: 2018/08/21 08:36:49 by dtheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void				ft_draw_menu_str_info(t_env *env)
{
	ft_ttf_render_txt_b_menu(env, STR_INFO, env->menu.cyan,
			(SDL_Rect){env->menu.titles_pos[0][0],
			env->menu.titles_pos[0][1], 0, 0});
	ft_ttf_render_txt_b_menu(env, "FPS", env->menu.orange,
	env->menu.str_rect[1]);
	ft_ttf_render_txt_b_menu(env, "WIDTH", env->menu.orange,
	env->menu.str_rect[2]);
	ft_ttf_render_txt_b_menu(env, env->menu.width_val,
	env->menu.white, env->menu.width_rect);
	ft_ttf_render_txt_b_menu(env, "HEIGHT", env->menu.orange,
	env->menu.str_rect[3]);
	ft_ttf_render_txt_b_menu(env, env->menu.height_val,
	env->menu.white, env->menu.height_rect);
	ft_ttf_render_txt_b_menu(env, "REFLECT", env->menu.orange,
	env->menu.str_rect[6]);
	ft_ttf_render_txt_b_menu(env, env->menu.limit_val,
	env->menu.white, env->menu.limit_rect);
	ft_draw_menu_str_info2(env);
}

static void				ft_draw_menu_str_postp(t_env *env)
{
	ft_ttf_render_txt_b_menu(env, STR_POST, env->menu.violet,
	(SDL_Rect){env->menu.titles_pos[1][0], env->menu.titles_pos[1][1], 0, 0});
	ft_ttf_render_txt_b_menu(env, "FILTER", env->menu.orange,
		env->menu.str_rect[1]);
	ft_draw_menu_str_filter(env);
	ft_ttf_render_txt_b_menu(env, "BLUR", env->menu.orange,
		env->menu.str_rect[2]);
	ft_ttf_render_txt_b_menu(env, "CEL-SHADING", env->menu.orange,
		env->menu.str_rect[3]);
	ft_ttf_render_txt_b_menu(env, "ANTI-ALIAS", env->menu.orange,
		env->menu.str_rect[4]);
	ft_ttf_render_txt_b_menu(env, "STEREOSCOPY", env->menu.orange,
		env->menu.str_rect[5]);
}

static void				ft_draw_menu_str_param(t_env *env)
{
	static const char	*str[] = {"   MOVE", "  ROTATE"};

	ft_ttf_render_txt_b_menu(env, str[env->menu.move_or_rot], env->menu.orange,
		env->menu.str_rect[1]);
	ft_ttf_render_txt_b_menu(env, STR_PARAM, env->menu.green,
	(SDL_Rect){env->menu.titles_pos[3][0], env->menu.titles_pos[3][1], 0, 0});
	ft_draw_slider_ambient(env);
	ft_draw_slider_fov(env);
}

void					ft_draw_menu_str(t_env *env)
{
	static void			(*f_menu_str[4])(t_env*) = {&ft_draw_menu_str_info,
												&ft_draw_menu_str_postp,
												&ft_draw_menu_str_editor,
												&ft_draw_menu_str_param};

	f_menu_str[(int)env->menu.menu](env);
}
