/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtheo <dtheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/30 14:30:48 by nsikora           #+#    #+#             */
/*   Updated: 2018/08/20 18:46:31 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	init_color(t_rt *rt, int i)
{
	(rt->objs + i)->color.byte[RED] = 255;
	(rt->objs + i)->color.byte[GREEN] = 255;
	(rt->objs + i)->color.byte[BLUE] = 255;
	(rt->objs + i)->color.byte[ALPHA] = 255;
}

static void	init_env_obj(t_rt *rt, int i, int nb_obj)
{
	if (i == nb_obj - 1)
		(rt->objs + i)->type = -1;
	*(rt->objs + i) = ft_new_obj();
	(rt->objs + i)->type = -1;
	(rt->objs + i)->scl[0] = 0;
	(rt->objs + i)->scl[1] = 0;
	(rt->objs + i)->scl[2] = 0;
	init_color(rt, i);
}

static void	init_env_light(t_rt *rt, int i, int nb_light)
{
	if (i == nb_light - 1)
	{
		(rt->lights + i)->intensity = -1;
		return ;
	}
	(rt->lights + i)->pos[V_X] = 0;
	(rt->lights + i)->pos[V_Y] = 100;
	(rt->lights + i)->pos[V_Z] = 10;
	(rt->lights + i)->dir[V_X] = 0;
	(rt->lights + i)->dir[V_Y] = 0;
	(rt->lights + i)->dir[V_Z] = 0;
	(rt->lights + i)->intensity = 0.2;
	(rt->lights + i)->color.byte[RED] = 255;
	(rt->lights + i)->color.byte[GREEN] = 255;
	(rt->lights + i)->color.byte[BLUE] = 255;
	(rt->lights + i)->color.byte[ALPHA] = 255;
}

void		init_env_ui(t_env *env)
{
	ft_init_quat_with_rot((t_vec){0, 45, 0}, env->rt.cam_rot);
	env->param.quit = 1;
	env->param.change = 1;
	env->param.menu_change = 1;
	env->param.max_fps = DEFAULT_FPS - 1;
	env->rt_param.fov = DEFAULT_FOV;
	env->preview_param.fov = DEFAULT_FOV;
	env->param.step = DEFAULT_STEP;
	env->param.width = WIDTH;
	env->param.height = HEIGHT;
	env->rt_param.ambient = 0.3;
	env->preview_param.ambient = 0.3;
	env->rt_param.r_limit = 0;
	env->rt_param.post = 0;
	env->rt_param.color = F_RED;
	env->rt_param.border = 0;
	env->rt_param.stereo = 0;
	env->rt_param.compute = 1;
	env->preview_param.compute = 1;
}

void		init_env_info(int nb_obj, int nb_light, t_rt *rt)
{
	int		i;

	i = 0;
	while (i <= nb_obj)
	{
		init_env_obj(rt, i, nb_obj);
		i++;
	}
	i = 0;
	while (i <= nb_light)
	{
		init_env_light(rt, i, nb_light);
		i++;
	}
}
