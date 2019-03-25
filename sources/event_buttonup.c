/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_buttonup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbard <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 18:42:26 by jbard             #+#    #+#             */
/*   Updated: 2018/08/21 13:02:46 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** ft_event_buttonup:
**
** Create an event when a mouse button is released.
*/

static void	ft_event_menu_editor(t_env *env)
{
	if (ft_event_slider_color(env))
		return ;
	if (env->param.mouse_pos_y < (int)env->menu.button_coor[1].h)
	{
		env->menu.editor_switch++;
		if (env->menu.editor_switch > 2)
			env->menu.editor_switch = 0;
		env->param.menu_change = 1;
		env->menu.redraw = 1;
		return ;
	}
	else if (env->menu.editor_switch == 0)
	{
		if (ft_event_slider_trans(env))
			return ;
		if (ft_event_slider_reflect(env))
			return ;
		if (ft_event_slider_refract(env))
			return ;
		ft_event_slider_spec(env);
	}
	else if (env->menu.editor_switch == 1)
		ft_event_menu_editor2(env);
	else if (env->menu.editor_switch == 2)
		ft_event_menu_editor3(env);
}

static void	ft_event_menu_param(t_env *env)
{
	if (env->param.mouse_pos_y < (int)env->menu.button_coor[1].h)
	{
		env->menu.move_or_rot = !env->menu.move_or_rot;
		env->param.menu_change = 1;
		env->menu.redraw = 1;
	}
	else if (ft_event_slider_fov(env))
		return ;
	else
		ft_event_slider_ambient(env);
}

void		ft_copy_param_content(t_rt_param *src, t_rt_param *dest)
{
	dest->border = src->border;
	dest->post = src->post;
	dest->color = src->color;
	dest->stereo = src->stereo;
	dest->scale = src->scale;
	dest->ambient = src->ambient;
	dest->r_limit = src->r_limit;
	dest->compute = 1;
}

static void	ft_event_menu_buttons(t_env *env)
{
	if (env->menu.tmp_menu == 4)
		ft_event_screenshot(env);
	else
	{
		if (env->menu.tmp_menu == 5)
		{
			ft_copy_param_content(&env->rt_param, &env->preview_param);
			env->param.menu_change = 1;
			env->menu.redraw = 1;
		}
		else if (env->menu.tmp_menu == 6)
			ft_copy_param_content(&env->preview_param, &env->rt_param);
		env->param.change = 1;
	}
}

void		ft_event_buttonup(t_env *env)
{
	static void (*f_menu_event[3])(t_env*) = {&ft_event_menu_postp,
											&ft_event_menu_editor,
											&ft_event_menu_param};

	if (env->event.button.button == SDL_BUTTON_LEFT)
	{
		if (env->param.mouse_pos_x > env->menu.rt_rect.x)
			ft_selector(env);
		else if (env->param.mouse_pos_x > (int)env->menu.sub_menu_coor[0] &&
				env->param.mouse_pos_y > (int)env->menu.button_coor[0].h &&
				env->menu.menu > 0)
			f_menu_event[(int)env->menu.menu - 1](env);
		else if (env->menu.tmp_menu < 4)
		{
			env->menu.menu = env->menu.tmp_menu;
			env->param.menu_change = 1;
			env->menu.redraw = 1;
		}
		else
			ft_event_menu_buttons(env);
	}
}
