/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_texture_mode.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtheo <dtheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 16:21:45 by nsikora           #+#    #+#             */
/*   Updated: 2018/08/21 11:41:48 by nsikora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	fill_texture_mode(t_json_obj *j_obj, t_rt *rt, int i)
{
	if (ft_strcmp(j_obj->info->str, "refract") == 0
			&& *(float *)(j_obj->info->value) <= 2
			&& *(float *)(j_obj->info->value) >= 0.8)
		(rt->objs + i)->refract = *(float *)(j_obj->info->value);
	if (ft_strcmp(j_obj->info->str, "texture mode") == 0
			&& *(float *)(j_obj->info->value) <= 2
			&& *(float *)(j_obj->info->value) >= 0)
		(rt->objs + i)->texture_mode = *(float *)(j_obj->info->value);
	else if (ft_strcmp(j_obj->info->str, "texture scale") == 0
			&& *(float *)(j_obj->info->value) > 0)
		(rt->objs + i)->texture_scl = ceil(*(float *)(j_obj->info->value));
}
