/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slider_trans.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeigne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 18:18:52 by ppeigne           #+#    #+#             */
/*   Updated: 2018/08/20 18:20:17 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ft_init_slider_trans(t_menu *menu)
{
	ft_update_slider(menu, &menu->trans, menu->trans_rect, 4);
	menu->trans.empty.rgb = (int)0xFFFAFAFA;
	menu->trans.fill = (t_color)SOLARIZED_ACCENT_YELLOW;
	menu->trans.min = 0;
	menu->trans.max = 1;
	menu->trans.val = 0;
}

int			ft_event_slider_trans(t_env *env)
{
	if (ft_event_slider(env, &env->menu.trans, env->param.mouse_pos_x,
			env->param.mouse_pos_y))
	{
		if (env->menu.selected_obj >= 0)
		{
			env->rt.objs[env->menu.selected_obj].trans = env->menu.trans.val;
			ft_rebuild_objs(env);
			env->rt_param.compute = 1;
			env->preview_param.compute = 1;
			env->param.change = 1;
		}
		if (env->menu.trans_val)
			free(env->menu.trans_val);
		env->menu.trans_val = ft_str_percentage(env->menu.trans.val);
		return (1);
	}
	return (0);
}

void		ft_compute_str_trans(t_env *env)
{
	int			width;
	int			height;

	TTF_SizeText(env->pt_mono, "TRANS  ", &width, &height);
	if (env->menu.trans_val)
		free(env->menu.trans_val);
	env->menu.trans_val = ft_str_percentage(env->menu.trans.val);
	env->menu.trans_rect = (SDL_Rect){env->menu.sub_menu_coor[0] + width,
		env->menu.str_rect[4].y - env->menu.button_coor[0].h / 3, 0, height};
}

void		ft_draw_slider_trans(t_env *env)
{
	SDL_Rect	rect;

	rect = env->menu.str_rect[4];
	rect.y -= env->menu.button_coor[0].h / 3;
	ft_ttf_render_txt_b_menu(env, "TRANS", env->menu.orange, rect);
	ft_ttf_render_txt_b_menu(env, env->menu.trans_val,
	env->menu.white, env->menu.trans_rect);
	ft_draw_slider(&env->menu, &env->menu.trans);
}
