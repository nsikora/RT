/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slider_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeigne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 18:15:42 by ppeigne           #+#    #+#             */
/*   Updated: 2018/08/20 18:18:03 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ft_draw_slider_color(t_menu *menu)
{
	int		i;
	t_color	mix;

	mix.rgb = 0xFF000000;
	i = -1;
	while (++i < 3)
	{
		ft_draw_slider(menu, menu->color + i);
		mix.byte[i] = floor(menu->color[i].val);
	}
	ft_draw_square(menu->color_coor, (int *)menu->lay_base->pixels,
		menu->lay_base->w, mix.rgb);
}

void		ft_update_slider_color(t_menu *menu)
{
	int		i;
	size_t	zone[4];
	size_t	space;
	size_t	height;
	size_t	color_width;

	zone[0] = menu->sub_menu_coor[0] + 10;
	zone[1] = menu->button_coor[6].y;
	zone[2] = menu->sub_menu_coor[2] - 10;
	zone[3] = menu->button_coor[6].h;
	space = (zone[3] - zone[1]) / 3;
	height = 0.2 * (zone[3] - zone[1]);
	color_width = 0.2 * (zone[2] - zone[0]);
	i = -1;
	while (++i < 3)
	{
		menu->color[i].coor[0] = zone[0];
		menu->color[i].coor[1] = zone[1] + space / 2 + space * i;
		menu->color[i].length = zone[2] - zone[0] - 10 - color_width;
		menu->color[i].thick = height;
	}
	menu->color_coor[0] = menu->color[0].coor[0] + menu->color[0].length + 10;
	menu->color_coor[1] = menu->color[0].coor[1] - menu->color[0].thick / 2;
	menu->color_coor[2] = menu->color_coor[0] + color_width;
	menu->color_coor[3] = menu->color[2].coor[1] + menu->color[2].thick / 2;
}

void		ft_init_slider_color(t_menu *menu)
{
	int		i;
	t_color	c;

	ft_update_slider_color(menu);
	i = -1;
	while (++i < 3)
	{
		c.rgb = 0xFFCFCFCF;
		c.byte[i] = 255;
		menu->color[i].empty = c;
		c.rgb = 0xFF000000;
		c.byte[i] = 255;
		menu->color[i].fill = c;
		menu->color[i].min = 0;
		menu->color[i].max = 255;
		menu->color[i].val = 100 + i * 50;
	}
}

int			ft_event_slider_color(t_env *env)
{
	int		i;
	int		refresh;

	i = -1;
	refresh = 0;
	while (++i < 3)
	{
		if (ft_event_slider(env, env->menu.color + i, env->param.mouse_pos_x,
				env->param.mouse_pos_y) && env->menu.selected_obj >= 0)
		{
			env->menu.last_color.byte[i] = env->menu.color[i].val;
			refresh = 1;
		}
	}
	if (refresh)
	{
		ft_rebuild_objs(env);
		env->rt_param.compute = 1;
		env->preview_param.compute = 1;
		env->param.change = 1;
		return (1);
	}
	return (0);
}
