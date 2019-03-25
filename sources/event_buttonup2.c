/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_buttonup2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtheo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 08:36:26 by dtheo             #+#    #+#             */
/*   Updated: 2018/08/21 08:36:29 by dtheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	ft_event_menu_editor3_mode(t_env *env)
{
	int		i;

	if (env->param.mouse_pos_y < (int)env->menu.button_coor[5].h &&
		env->param.mouse_pos_y > (int)env->menu.button_coor[4].h)
	{
		env->param.menu_change = 1;
		env->menu.redraw = 1;
		env->menu.tex_mode_switch++;
		if (env->menu.tex_mode_switch > 2)
			env->menu.tex_mode_switch = 0;
		if (env->menu.selected_obj >= 0)
		{
			i = env->menu.tex_mode_switch;
			env->rt.objs[(int)env->menu.selected_obj].texture_mode = i;
			ft_rebuild_objs(env);
			env->rt_param.compute = 1;
			env->preview_param.compute = 1;
			env->param.change = 1;
		}
		return ;
	}
	if (ft_event_slider_tex(env))
		return ;
	ft_event_slider_tex_scl(env);
}

void		ft_event_menu_editor3(t_env *env)
{
	if (env->param.mouse_pos_y < (int)env->menu.button_coor[2].h &&
		env->param.mouse_pos_y > (int)env->menu.button_coor[1].h)
	{
		env->param.menu_change = 1;
		env->menu.redraw = 1;
		env->menu.tex_switch++;
		if (env->menu.tex_switch > 2)
			env->menu.tex_switch = 0;
		if (env->menu.selected_obj < 0)
			return ;
		if (env->menu.tex_switch == 0)
			env->menu.tex.val =
				env->menu.last_tex;
		else if (env->menu.tex_switch == 1)
			env->menu.tex.val =
				env->rt.objs[(int)env->menu.selected_obj].texture_norm;
		else if (env->menu.tex_switch == 2)
			env->menu.tex.val =
				env->rt.objs[(int)env->menu.selected_obj].texture_spec;
		if (env->menu.tex_val)
			free(env->menu.tex_val);
		env->menu.tex_val = ft_name_slider_tex(env);
		return ;
	}
	ft_event_menu_editor3_mode(env);
}

static void	ft_event_menu_editor2_type(t_env *env)
{
	env->rt.objs[(int)env->menu.selected_obj].type = env->menu.type_switch;
	if (env->menu.type_switch == ID_CONE &&
			(env->rt.objs[(int)env->menu.selected_obj].scl[0] < 0 ||
			env->rt.objs[(int)env->menu.selected_obj].scl[0] > M_PI))
		env->rt.objs[(int)env->menu.selected_obj].scl[0] = M_PI_4;
	else if (env->menu.type_switch == ID_CUBE)
	{
		if (env->rt.objs[(int)env->menu.selected_obj].scl[1] <= 0)
			env->rt.objs[(int)env->menu.selected_obj].scl[1] = 1;
		if (env->rt.objs[(int)env->menu.selected_obj].scl[2] <= 0)
			env->rt.objs[(int)env->menu.selected_obj].scl[2] = 1;
	}
	ft_rebuild_objs(env);
	env->rt_param.compute = 1;
	env->preview_param.compute = 1;
	env->param.change = 1;
}

void		ft_event_menu_editor2(t_env *env)
{
	if (env->param.mouse_pos_y < (int)env->menu.button_coor[3].h &&
		env->param.mouse_pos_y > (int)env->menu.button_coor[2].h)
		ft_add_obj(env);
	else if (env->param.mouse_pos_y < (int)env->menu.button_coor[2].h &&
		env->param.mouse_pos_y > (int)env->menu.button_coor[1].h)
	{
		env->menu.type_switch++;
		if (env->menu.type_switch > 4)
			env->menu.type_switch = 0;
		env->param.menu_change = 1;
		env->menu.redraw = 1;
		if (env->menu.selected_obj >= 0)
			ft_event_menu_editor2_type(env);
	}
}
