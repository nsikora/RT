/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slider_reflect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeigne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 18:23:17 by ppeigne           #+#    #+#             */
/*   Updated: 2018/08/20 18:23:59 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			ft_init_slider_reflect(t_menu *menu)
{
	ft_update_slider(menu, &menu->reflection, menu->reflect_rect, 3);
	menu->reflection.empty.rgb = (int)0xFFFAFAFA;
	menu->reflection.fill = (t_color)SOLARIZED_ACCENT_ORANGE;
	menu->reflection.min = 0;
	menu->reflection.max = 1;
	menu->reflection.val = 0;
}

int				ft_event_slider_reflect(t_env *env)
{
	if (ft_event_slider(env, &env->menu.reflection, env->param.mouse_pos_x,
			env->param.mouse_pos_y))
	{
		if (env->menu.selected_obj >= 0)
		{
			env->rt.objs[env->menu.selected_obj].reflect =
				env->menu.reflection.val;
			ft_rebuild_objs(env);
			env->rt_param.compute = 1;
			env->preview_param.compute = 1;
			env->param.change = 1;
		}
		if (env->menu.reflect_val)
			free(env->menu.reflect_val);
		env->menu.reflect_val = ft_str_percentage(env->menu.reflection.val);
		return (1);
	}
	return (0);
}

void			ft_compute_str_reflect(t_env *env)
{
	int			width;
	int			height;

	TTF_SizeText(env->pt_mono, "REFL  ", &width, &height);
	if (env->menu.reflect_val)
		free(env->menu.reflect_val);
	env->menu.reflect_val = ft_str_percentage(env->menu.reflection.val);
	env->menu.reflect_rect = (SDL_Rect){env->menu.sub_menu_coor[0] + width,
		env->menu.str_rect[3].y - env->menu.button_coor[0].h / 3, 0, height};
}

void			ft_draw_slider_reflect(t_env *env)
{
	SDL_Rect	rect;

	rect = env->menu.str_rect[3];
	rect.y -= env->menu.button_coor[0].h / 3;
	ft_ttf_render_txt_b_menu(env, "REFL", env->menu.orange, rect);
	ft_ttf_render_txt_b_menu(env, env->menu.reflect_val,
		env->menu.white, env->menu.reflect_rect);
	ft_draw_slider(&env->menu, &env->menu.reflection);
}
