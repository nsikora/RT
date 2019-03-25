/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_rt_param.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsikora <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 12:25:39 by nsikora           #+#    #+#             */
/*   Updated: 2018/08/21 12:03:58 by nsikora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	assign_ui(int nb, t_json_obj *j_obj, t_env *env)
{
	if ((ft_strcmp(j_obj->info->str, "width") == 0)
		&& nb >= 500 && nb <= 2560)
		env->param.width = nb;
	if ((ft_strcmp(j_obj->info->str, "height") == 0)
		&& nb >= 500 && nb <= 1395)
		env->param.height = nb;
	if ((ft_strcmp(j_obj->info->str, "fov") == 0)
		&& nb >= 1 && nb <= 179)
		env->rt_param.fov = nb;
	if ((ft_strcmp(j_obj->info->str, "step") == 0)
		&& nb >= 0.5 && nb <= 100)
		env->param.step = nb;
	if ((ft_strcmp(j_obj->info->str, "max_fps") == 0)
		&& nb >= 1 && nb <= 120)
		env->param.max_fps = nb;
}

void		fill_ui(t_json_obj *j_obj, t_env *env)
{
	float	nb;
	t_info	*tmp;

	while (j_obj->info)
	{
		nb = *(float *)(j_obj->info->value);
		assign_ui(nb, j_obj, env);
		tmp = j_obj->info;
		j_obj->info = j_obj->info->next;
		free(tmp->str);
		free(tmp->value);
		free(tmp);
	}
}

static void	fill_post_color(t_json_obj *j_obj, t_env *env, char *str)
{
	if ((ft_strcmp(j_obj->info->str, "color") == 0)
		&& (ft_strcmp(str, "red") == 0))
		env->rt_param.color = 0;
	if ((ft_strcmp(j_obj->info->str, "color") == 0)
		&& (ft_strcmp(str, "green") == 0))
		env->rt_param.color = 1;
	if ((ft_strcmp(j_obj->info->str, "color") == 0)
		&& (ft_strcmp(str, "blue") == 0))
		env->rt_param.color = 2;
	if ((ft_strcmp(j_obj->info->str, "post") == 0)
		&& (ft_strcmp(str, "blur") == 0))
		env->rt_param.post = 1;
	if ((ft_strcmp(j_obj->info->str, "post") == 0)
		&& (ft_strcmp(str, "black & white") == 0))
		env->rt_param.post = 2;
	if ((ft_strcmp(j_obj->info->str, "post") == 0)
		&& (ft_strcmp(str, "color") == 0))
		env->rt_param.post = 3;
	if ((ft_strcmp(j_obj->info->str, "post") == 0)
		&& (ft_strcmp(str, "negative") == 0))
		env->rt_param.post = 5;
}

void		fill_filter(t_json_obj *j_obj, t_env *env)
{
	char	*str;
	t_info	*tmp;

	while (j_obj->info)
	{
		str = (char *)(j_obj->info->value);
		if ((ft_strcmp(j_obj->info->str, "border") == 0)
			&& (ft_strcmp(str, "cartoon") == 0))
			env->rt_param.border = 1;
		if ((ft_strcmp(j_obj->info->str, "border") == 0)
			&& (ft_strcmp(str, "antialiasing") == 0))
			env->rt_param.border = 2;
		if ((ft_strcmp(j_obj->info->str, "stereoscopy") == 0)
			&& (ft_strcmp(str, "on") == 0))
			env->rt_param.stereo = 1;
		fill_post_color(j_obj, env, str);
		tmp = j_obj->info;
		j_obj->info = j_obj->info->next;
		free(tmp->str);
		free(tmp->value);
		free(tmp);
	}
}

void		fill_texture(t_json_obj *j_obj, t_rt *rt)
{
	t_info	*tmp;
	int		i;

	i = 0;
	if (!j_obj->info)
		return ;
	while (j_obj->info)
	{
		if ((ft_strcmp(j_obj->info->str, "path") == 0))
		{
			rt->textures[i] = ft_texture_load((char *)(j_obj->info->value));
			i++;
		}
		tmp = j_obj->info;
		j_obj->info = j_obj->info->next;
		free(tmp->str);
		free(tmp->value);
		free(tmp);
	}
}
