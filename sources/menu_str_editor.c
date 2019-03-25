/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_str_editor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtheo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 08:37:00 by dtheo             #+#    #+#             */
/*   Updated: 2018/08/21 08:37:02 by dtheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void				ft_draw_menu_str_editor2(t_env *env)
{
	static const char	*tex[] = {"TEXTURE  >", "BUMP MAP > ", "SPEC MAP >"};
	static const char	*tmode[] = {"SPHERIC  >", "CYLINDRIC> ", "PLANAR   >"};
	static const char	*type[] = {"SPHERE   >", "CONE     > ",
									"PLANE    >", "CYLINDER >", "CUBE     >"};

	if (env->menu.editor_switch == 1)
	{
		ft_ttf_render_txt_b_menu(env, type[env->menu.type_switch],
			env->menu.orange, env->menu.str_rect[2]);
		ft_ttf_render_txt_b_menu(env, "ADD OBJ",
			env->menu.orange, env->menu.str_rect[3]);
	}
	else
	{
		ft_ttf_render_txt_b_menu(env, tex[env->menu.tex_switch],
			env->menu.orange, env->menu.str_rect[2]);
		ft_ttf_render_txt_b_menu(env, tmode[env->menu.tex_mode_switch],
			env->menu.orange, env->menu.str_rect[5]);
		ft_draw_slider_tex(env);
		ft_draw_slider_tex_scl(env);
	}
}

void					ft_draw_menu_str_editor(t_env *env)
{
	static const char	*pge[] = {" PAGE 1/3", " PAGE 2/3", " PAGE 3/3"};

	ft_ttf_render_txt_b_menu(env, pge[env->menu.editor_switch],
		env->menu.grey, env->menu.str_rect[1]);
	ft_ttf_render_txt_b_menu(env, STR_EDIT, env->menu.red,
	(SDL_Rect){env->menu.titles_pos[2][0], env->menu.titles_pos[2][1], 0, 0});
	ft_draw_slider_color(&env->menu);
	if (env->menu.editor_switch == 0)
	{
		ft_draw_slider_reflect(env);
		ft_draw_slider_refract(env);
		ft_draw_slider_spec(env);
		ft_draw_slider_trans(env);
	}
	else
		ft_draw_menu_str_editor2(env);
}
