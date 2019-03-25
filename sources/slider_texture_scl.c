/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slider_texture_scl.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtheo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 08:37:27 by dtheo             #+#    #+#             */
/*   Updated: 2018/08/21 08:37:28 by dtheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			ft_init_slider_tex_scl(t_menu *menu)
{
	ft_update_slider(menu, &menu->tex_scl, menu->tex_scl_rect, 4);
	menu->tex_scl.empty.rgb = (int)0xFFFAFAFA;
	menu->tex_scl.fill = (t_color)SOLARIZED_ACCENT_YELLOW;
	menu->tex_scl.min = 1;
	menu->tex_scl.max = 50;
	menu->tex_scl.val = 1;
}

int				ft_event_slider_tex_scl(t_env *env)
{
	if (ft_event_slider(env, &env->menu.tex_scl, env->param.mouse_pos_x,
			env->param.mouse_pos_y))
	{
		if (env->menu.selected_obj >= 0)
		{
			env->rt.objs[env->menu.selected_obj].texture_scl =
				(size_t)floor(env->menu.tex_scl.val);
			ft_rebuild_objs(env);
			env->rt_param.compute = 1;
			env->preview_param.compute = 1;
			env->param.change = 1;
		}
		if (env->menu.tex_scl_val)
			free(env->menu.tex_scl_val);
		env->menu.tex_scl_val = ft_itoa(floor(env->menu.tex_scl.val));
		return (1);
	}
	return (0);
}

void			ft_compute_str_tex_scl(t_env *env)
{
	int			width;
	int			height;

	if (env->menu.tex_scl.min == 0)
		ft_init_slider_tex_scl(&env->menu);
	TTF_SizeText(env->pt_mono, "TEX SCL  ", &width, &height);
	if (env->menu.tex_scl_val)
		free(env->menu.tex_scl_val);
	env->menu.tex_scl_val = ft_itoa(floor(env->menu.tex_scl.val));
	env->menu.tex_scl_rect = (SDL_Rect){env->menu.sub_menu_coor[0] + width,
		env->menu.str_rect[4].y - env->menu.button_coor[0].h / 3, 0, height};
}

void			ft_draw_slider_tex_scl(t_env *env)
{
	SDL_Rect	rect;

	rect = env->menu.str_rect[4];
	rect.y -= env->menu.button_coor[0].h / 3;
	ft_ttf_render_txt_b_menu(env, "TEX SCL", env->menu.orange, rect);
	ft_ttf_render_txt_b_menu(env, env->menu.tex_scl_val,
	env->menu.white, env->menu.tex_scl_rect);
	ft_draw_slider(&env->menu, &env->menu.tex_scl);
}
