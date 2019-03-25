/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slider_refract.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeigne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 18:21:56 by ppeigne           #+#    #+#             */
/*   Updated: 2018/08/20 18:22:53 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			ft_init_slider_refract(t_menu *menu)
{
	ft_update_slider(menu, &menu->refraction, menu->refract_rect, 5);
	menu->refraction.empty.rgb = (int)0xFFFAFAFA;
	menu->refraction.fill = (t_color)SOLARIZED_ACCENT_GREEN;
	menu->refraction.min = 0.5;
	menu->refraction.max = 2;
	menu->refraction.val = 1;
}

int				ft_event_slider_refract(t_env *env)
{
	if (ft_event_slider(env, &env->menu.refraction, env->param.mouse_pos_x,
			env->param.mouse_pos_y))
	{
		if (env->menu.selected_obj >= 0)
		{
			env->rt.objs[env->menu.selected_obj].refract =
				env->menu.refraction.val;
			ft_rebuild_objs(env);
			env->rt_param.compute = 1;
			env->preview_param.compute = 1;
			env->param.change = 1;
		}
		if (env->menu.refract_val)
			free(env->menu.refract_val);
		env->menu.refract_val = ft_ftoa(env->menu.refraction.val, 2);
		return (1);
	}
	return (0);
}

void			ft_compute_str_refract(t_env *env)
{
	int			width;
	int			height;

	TTF_SizeText(env->pt_mono, "REFR  ", &width, &height);
	if (env->menu.refract_val)
		free(env->menu.refract_val);
	if (env->menu.refraction.val > 0)
		env->menu.refract_val = ft_ftoa(env->menu.refraction.val, 2);
	else
		env->menu.refract_val = ft_strdup("1.00");
	env->menu.refract_rect = (SDL_Rect){env->menu.sub_menu_coor[0] + width,
		env->menu.str_rect[5].y - env->menu.button_coor[0].h / 3, 0, height};
}

void			ft_draw_slider_refract(t_env *env)
{
	SDL_Rect	rect;

	rect = env->menu.str_rect[5];
	rect.y -= env->menu.button_coor[0].h / 3;
	ft_ttf_render_txt_b_menu(env, "REFR", env->menu.orange, rect);
	ft_ttf_render_txt_b_menu(env, env->menu.refract_val,
	env->menu.white, env->menu.refract_rect);
	ft_draw_slider(&env->menu, &env->menu.refraction);
}
