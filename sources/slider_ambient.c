/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slider_ambient.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeigne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 18:24:20 by ppeigne           #+#    #+#             */
/*   Updated: 2018/08/20 18:28:19 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			ft_init_slider_ambient(t_env *env, t_menu *menu)
{
	ft_update_slider(menu, &menu->ambient, menu->ambient_rect, 3);
	menu->ambient.empty.rgb = (int)0xFFFAFAFA;
	menu->ambient.fill = (t_color)SOLARIZED_ACCENT_GREEN;
	menu->ambient.min = 0;
	menu->ambient.max = 1;
	menu->ambient.val = env->preview_param.ambient;
}

int				ft_event_slider_ambient(t_env *env)
{
	if (ft_event_slider(env, &env->menu.ambient, env->param.mouse_pos_x,
			env->param.mouse_pos_y))
	{
		env->preview_param.ambient = env->menu.ambient.val;
		if (env->menu.ambient_val)
			free(env->menu.ambient_val);
		env->menu.ambient_val = ft_ftoa(env->menu.ambient.val, 2);
		env->preview_param.compute = 1;
		env->param.change = 1;
		return (1);
	}
	return (0);
}

void			ft_compute_str_ambient(t_env *env)
{
	int			width;
	int			height;

	TTF_SizeText(env->pt_mono, "LIGHT  ", &width, &height);
	if (env->menu.ambient_val)
		free(env->menu.ambient_val);
	env->menu.ambient_val = ft_ftoa(env->preview_param.ambient, 2);
	env->menu.ambient_rect = (SDL_Rect){env->menu.sub_menu_coor[0] + width,
	env->menu.str_rect[3].y - env->menu.button_coor[0].h / 3, 0, height};
}

void			ft_draw_slider_ambient(t_env *env)
{
	SDL_Rect	rect;

	rect = env->menu.str_rect[3];
	rect.y -= env->menu.button_coor[0].h / 3;
	ft_ttf_render_txt_b_menu(env, "LIGHT", env->menu.orange, rect);
	ft_ttf_render_txt_b_menu(env, env->menu.ambient_val,
		env->menu.white, env->menu.ambient_rect);
	ft_draw_slider(&env->menu, &env->menu.ambient);
}
