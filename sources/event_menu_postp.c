/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_menu_postp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbard <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 18:47:00 by jbard             #+#    #+#             */
/*   Updated: 2018/08/20 18:47:01 by jbard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	ft_postp_filter(t_env *env)
{
	if (env->preview_param.post == P_COLOR)
	{
		if (env->preview_param.color != 2)
			env->preview_param.color++;
		else
			env->preview_param.post = P_GREY;
	}
	else if (env->preview_param.post == P_GREY)
		env->preview_param.post = P_NEG;
	else if (env->preview_param.post == P_NEG)
		env->preview_param.post = 0;
	else
	{
		env->preview_param.post = P_COLOR;
		env->preview_param.color = 0;
		env->preview_param.stereo = 0;
	}
}

static void	ft_postp_blur(t_env *env)
{
	if (env->preview_param.post == P_BLUR)
		env->preview_param.post = 0;
	else
	{
		env->preview_param.post = P_BLUR;
		env->preview_param.stereo = 0;
	}
}

static void	ft_postp_stereo(t_env *env)
{
	if (env->preview_param.stereo == STEREO1)
	{
		env->preview_param.stereo = 0;
		env->preview_param.post = 0;
		env->preview_param.color = 0;
	}
	else
	{
		if (env->preview_param.border == ANTI_ALIASING)
			env->preview_param.border = 0;
		env->preview_param.stereo = STEREO1;
	}
}

static void	ft_postp_border(t_env *env, char param)
{
	if (env->preview_param.border == param)
		env->preview_param.border = 0;
	else
	{
		if (param == ANTI_ALIASING && env->preview_param.stereo)
		{
			env->preview_param.post = 0;
			env->preview_param.color = 0;
			env->preview_param.stereo = 0;
		}
		env->preview_param.border = param;
	}
}

void		ft_event_menu_postp(t_env *env)
{
	if (env->param.mouse_pos_y < (int)env->menu.button_coor[1].h)
		ft_postp_filter(env);
	else if (env->param.mouse_pos_y < (int)env->menu.button_coor[2].h)
		ft_postp_blur(env);
	else if (env->param.mouse_pos_y < (int)env->menu.button_coor[3].h)
		ft_postp_border(env, CELL_SHADING);
	else if (env->param.mouse_pos_y < (int)env->menu.button_coor[4].h)
		ft_postp_border(env, ANTI_ALIASING);
	else if (env->param.mouse_pos_y < (int)env->menu.button_coor[5].h)
		ft_postp_stereo(env);
	else if (env->param.mouse_pos_y < (int)env->menu.button_coor[6].h)
		return ;
	env->param.change = 1;
	env->preview_param.compute = 1;
	env->param.menu_change = 1;
	env->menu.redraw = 1;
}
