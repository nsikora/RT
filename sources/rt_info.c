/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_info.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsikora <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 17:39:22 by nsikora           #+#    #+#             */
/*   Updated: 2018/08/21 15:17:00 by nsikora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		fill_light(t_json_obj *j_obj, t_rt *rt, int i)
{
	t_info		*tmp;

	while (j_obj->info)
	{
		if (ft_strcmp(j_obj->info->str, "pos") == 0 ||
			ft_strcmp(j_obj->info->str, "dir") == 0 ||
			ft_strcmp(j_obj->info->str, "color") == 0)
			fill_tab_info(j_obj, rt, i);
		if (ft_strcmp(j_obj->info->str, "intensity") == 0)
			(rt->lights + i)->intensity = *(float*)(j_obj->info->value);
		tmp = j_obj->info;
		j_obj->info = j_obj->info->next;
		ft_free_temp(tmp);
	}
}

static void		fill_camera(t_json_obj *j_obj, t_env *env)
{
	float		*tab;
	t_info		*tmp;

	while (j_obj->info)
	{
		tab = (j_obj->info->value);
		if (ft_strcmp(j_obj->info->str, "pos") == 0)
		{
			env->rt.cam_pos[0] = tab[0];
			env->rt.cam_pos[1] = tab[1];
			env->rt.cam_pos[2] = tab[2];
		}
		if (ft_strcmp(j_obj->info->str, "rot") == 0)
			ft_init_quat_with_rot((t_vec){tab[0], tab[1], tab[2]},
			env->rt.cam_rot);
		tmp = j_obj->info;
		j_obj->info = j_obj->info->next;
		ft_free_temp(tmp);
	}
}

void			fill_object(t_json_obj *j_obj, t_rt_param *param,
				t_rt *rt, int i)
{
	if (ft_strcmp(j_obj->info->str, "spec") == 0
		&& *(float *)(j_obj->info->value) >= 0)
		(rt->objs + i)->spec = *(float *)(j_obj->info->value);
	if (*(float *)(j_obj->info->value) <= 1
		&& *(float *)(j_obj->info->value) >= 0)
	{
		if (ft_strcmp(j_obj->info->str, "trans") == 0)
			(rt->objs + i)->trans = *(float *)(j_obj->info->value);
		if (ft_strcmp(j_obj->info->str, "reflect") == 0)
			(rt->objs + i)->reflect = *(float *)(j_obj->info->value);
	}
	if (ft_strcmp(j_obj->info->str, "texture") == 0
			&& *(float *)(j_obj->info->value) < param->mem_objs.nb_tex
			&& *(float *)(j_obj->info->value) >= -3)
		(rt->objs + i)->texture = *(float *)(j_obj->info->value);
	if (ft_strcmp(j_obj->info->str, "bumpmapping") == 0
			&& *(float *)(j_obj->info->value) < param->mem_objs.nb_tex
			&& *(float *)(j_obj->info->value) >= -3)
		(rt->objs + i)->texture_norm = *(float *)(j_obj->info->value);
	if (ft_strcmp(j_obj->info->str, "specmapping") == 0
			&& *(float *)(j_obj->info->value) < param->mem_objs.nb_tex
			&& *(float *)(j_obj->info->value) >= -1)
		(rt->objs + i)->texture_spec = *(float *)(j_obj->info->value);
	fill_texture_mode(j_obj, rt, i);
}

static void		rt_node(t_json_obj *j_obj, t_env *env, int nb_obj, int nb_light)
{
	t_json_obj	*tmp;

	ft_putstr("Disclaimer: Invalid values in dataset will be ignored ");
	ft_putendl("and set to default. Only up to 300 objs will be read");
	while (j_obj)
	{
		if (ft_strcmp(j_obj->str, "ui") == 0)
			fill_ui(j_obj, env);
		if (ft_strcmp(j_obj->str, "texture") == 0)
			fill_texture(j_obj, &env->rt);
		if (ft_strcmp(j_obj->str, "filter") == 0)
			fill_filter(j_obj, env);
		if (ft_strcmp(j_obj->str, "light") == 0)
		{
			fill_light(j_obj, &env->rt, nb_light);
			nb_light++;
		}
		if (ft_strcmp(j_obj->str, "camera") == 0)
			fill_camera(j_obj, env);
		nb_obj = check_object(j_obj, env, nb_obj);
		tmp = j_obj;
		j_obj = j_obj->next;
		free(tmp->str);
		free(tmp);
	}
}

void			rt_info(char *path, t_env *env)
{
	t_json_obj	*j_obj;
	int			error;

	j_obj = ft_parse_file(path, &error, NULL, 0);
	env->rt_param.mem_objs.nb_obj = get_obj_nb(j_obj) + 1;
	env->rt_param.mem_objs.nb_light = get_light_nb(j_obj) + 1;
	env->rt_param.mem_objs.nb_tex = get_texture_nb(j_obj);
	env->preview_param.mem_objs.nb_obj = env->rt_param.mem_objs.nb_obj;
	env->preview_param.mem_objs.nb_light = env->rt_param.mem_objs.nb_light;
	env->preview_param.mem_objs.nb_tex = env->rt_param.mem_objs.nb_tex;
	put_nb_error(env);
	if (!(env->rt.objs = ft_memalloc(sizeof(t_obj)
		* (env->rt_param.mem_objs.nb_obj))))
		ft_error(MALLOC_ERROR);
	if (!(env->rt.lights = ft_memalloc(sizeof(t_light)
		* (env->rt_param.mem_objs.nb_light))))
		ft_error(MALLOC_ERROR);
	if (!(env->rt.textures = ft_memalloc(sizeof(t_tex)
		* (env->rt_param.mem_objs.nb_tex))))
		ft_error(MALLOC_ERROR);
	init_env_info(env->rt_param.mem_objs.nb_obj,
		env->rt_param.mem_objs.nb_light, &env->rt);
	init_env_ui(env);
	rt_node(j_obj, env, 0, 0);
}
