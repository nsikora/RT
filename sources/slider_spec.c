/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slider_spec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeigne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 18:20:48 by ppeigne           #+#    #+#             */
/*   Updated: 2018/08/20 18:21:42 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ft_init_slider_spec(t_menu *menu)
{
	ft_update_slider(menu, &menu->spec, menu->spec_rect, 2);
	menu->spec.empty.rgb = (int)0xFFFAFAFA;
	menu->spec.fill = (t_color)SOLARIZED_ACCENT_RED;
	menu->spec.min = 0;
	menu->spec.max = 50;
	menu->spec.val = 10;
}

int			ft_event_slider_spec(t_env *env)
{
	if (ft_event_slider(env, &env->menu.spec, env->param.mouse_pos_x,
			env->param.mouse_pos_y))
	{
		if (env->menu.selected_obj >= 0)
		{
			env->rt.objs[env->menu.selected_obj].spec =
				env->menu.spec.val;
			ft_rebuild_objs(env);
			env->rt_param.compute = 1;
			env->preview_param.compute = 1;
			env->param.change = 1;
		}
		if (env->menu.spec_val)
			free(env->menu.spec_val);
		env->menu.spec_val = ft_ftoa(env->menu.spec.val, 2);
		return (1);
	}
	return (0);
}

void		ft_compute_str_spec(t_env *env)
{
	int			width;
	int			height;

	TTF_SizeText(env->pt_mono, "SPEC  ", &width, &height);
	if (env->menu.spec_val)
		free(env->menu.spec_val);
	if (env->menu.spec.val > 0)
		env->menu.spec_val = ft_ftoa(env->menu.spec.val, 2);
	else
		env->menu.spec_val = ft_strdup("10.00");
	env->menu.spec_rect = (SDL_Rect){env->menu.sub_menu_coor[0] + width,
		env->menu.str_rect[2].y - env->menu.button_coor[0].h / 3, 0, height};
}

void		ft_draw_slider_spec(t_env *env)
{
	SDL_Rect	rect;

	rect = env->menu.str_rect[2];
	rect.y -= env->menu.button_coor[0].h / 3;
	ft_ttf_render_txt_b_menu(env, "SPEC", env->menu.orange, rect);
	ft_ttf_render_txt_b_menu(env, env->menu.spec_val,
	env->menu.white, env->menu.spec_rect);
	ft_draw_slider(&env->menu, &env->menu.spec);
}
