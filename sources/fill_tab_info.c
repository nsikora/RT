/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tab_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsikora <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 17:41:01 by nsikora           #+#    #+#             */
/*   Updated: 2018/08/21 12:00:26 by nsikora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	fill_tab_obj_next(t_json_obj *j_obj, float *tab, t_rt *rt, int i)
{
	if (ft_strcmp(j_obj->info->str, "color") == 0)
	{
		if (tab[2] >= 0 && tab[2] <= 255)
			(rt->objs + i)->color.byte[RED] = tab[2];
		if (tab[1] >= 0 && tab[1] <= 255)
			(rt->objs + i)->color.byte[GREEN] = tab[1];
		if (tab[0] >= 0 && tab[0] <= 255)
			(rt->objs + i)->color.byte[BLUE] = tab[0];
		if (tab[3] >= 0 && tab[3] <= 255)
			(rt->objs + i)->color.byte[ALPHA] = tab[3];
	}
	if (ft_strcmp(j_obj->info->str, "scl") == 0)
	{
		if (tab[0] > 0)
			(rt->objs + i)->scl[0] = tab[0];
		if (tab[1] > 0)
			(rt->objs + i)->scl[1] = tab[1];
		if (tab[2] > 0)
			(rt->objs + i)->scl[2] = tab[2];
	}
}

void		fill_tab_obj(t_json_obj *j_obj, t_rt *rt, int i)
{
	t_quat	rot_quat;
	float	*tab;

	tab = (j_obj->info->value);
	if (ft_strcmp(j_obj->info->str, "pos") == 0)
	{
		(rt->objs + i)->pos[V_X] = tab[0];
		(rt->objs + i)->pos[V_Y] = tab[1];
		(rt->objs + i)->pos[V_Z] = tab[2];
	}
	if (ft_strcmp(j_obj->info->str, "rot") == 0)
	{
		ft_init_quat_with_rot(tab, rot_quat);
		ft_quat_vec_mult(rot_quat, (rt->objs + i)->dir, (rt->objs + i)->dir);
	}
	fill_tab_obj_next(j_obj, tab, rt, i);
}

void		fill_tab_info(t_json_obj *j_obj, t_rt *rt, int i)
{
	float	*tab;

	tab = (float *)(j_obj->info->value);
	if (ft_strcmp(j_obj->info->str, "pos") == 0)
	{
		(rt->lights + i)->pos[0] = tab[0];
		(rt->lights + i)->pos[1] = tab[1];
		(rt->lights + i)->pos[2] = tab[2];
	}
	if (ft_strcmp(j_obj->info->str, "dir") == 0)
	{
		(rt->lights + i)->dir[0] = tab[0];
		(rt->lights + i)->dir[1] = tab[1];
		(rt->lights + i)->dir[2] = tab[2];
		ft_normalize((rt->lights + i)->dir, (rt->lights + i)->dir);
	}
	if (ft_strcmp(j_obj->info->str, "color") == 0)
	{
		(rt->lights + i)->color.byte[RED] = tab[2];
		(rt->lights + i)->color.byte[GREEN] = tab[1];
		(rt->lights + i)->color.byte[BLUE] = tab[0];
	}
}

void		get_env_obj_type(t_json_obj *j_obj, t_rt *rt, int i)
{
	if (ft_strcmp(j_obj->str, "sphere") == 0)
	{
		(rt->objs + i)->texture_mode = 0;
		(rt->objs + i)->type = ID_SPHERE;
	}
	else if (ft_strcmp(j_obj->str, "cube") == 0)
	{
		(rt->objs + i)->texture_mode = 0;
		(rt->objs + i)->type = ID_CUBE;
	}
	else if (ft_strcmp(j_obj->str, "plane") == 0)
	{
		(rt->objs + i)->texture_mode = 2;
		(rt->objs + i)->type = ID_PLANE;
		(rt->objs + i)->dir[V_Y] = 0;
		(rt->objs + i)->dir[V_Z] = 1;
	}
	else
	{
		if (ft_strcmp(j_obj->str, "cone") == 0)
			(rt->objs + i)->type = ID_CONE;
		if (ft_strcmp(j_obj->str, "cylinder") == 0)
			(rt->objs + i)->type = ID_CYLINDER;
		(rt->objs + i)->texture_mode = 1;
	}
}

int			check_object(t_json_obj *j_obj, t_env *env, int nb_obj)
{
	t_info	*temp;

	if (ft_strcmp(j_obj->str, "plane") == 0
		|| ft_strcmp(j_obj->str, "cone") == 0
		|| ft_strcmp(j_obj->str, "cylinder") == 0
		|| ft_strcmp(j_obj->str, "sphere") == 0
		|| ft_strcmp(j_obj->str, "cube") == 0)
	{
		get_env_obj_type(j_obj, &env->rt, nb_obj);
		while (j_obj->info)
		{
			if (ft_strcmp(j_obj->info->str, "pos") == 0
					|| ft_strcmp(j_obj->info->str, "rot") == 0
					|| ft_strcmp(j_obj->info->str, "scl") == 0
					|| ft_strcmp(j_obj->info->str, "color") == 0)
				fill_tab_obj(j_obj, &env->rt, nb_obj);
			fill_object(j_obj, &env->rt_param, &env->rt, nb_obj);
			temp = j_obj->info;
			j_obj->info = j_obj->info->next;
			(env->rt.objs + (nb_obj + 1))->type = -1;
			ft_free_temp(temp);
		}
		nb_obj++;
	}
	return (nb_obj);
}
