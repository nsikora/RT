/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_scroll.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbard <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 18:47:31 by jbard             #+#    #+#             */
/*   Updated: 2018/08/20 18:47:32 by jbard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	ft_scale_obj(t_obj *obj, t_vec scale)
{
	int		i;
	int		change;

	change = 0;
	i = -1;
	while (++i < 3)
	{
		if ((obj->type != ID_CONE || i != 0) &&
			obj->scl[i] > 0 && obj->scl[i] + scale[i] > 0)
		{
			change = 1;
			obj->scl[i] += scale[i];
		}
	}
	return (change);
}

void		ft_event_scroll(t_env *env)
{
	int		y;
	t_vec	scale;

	y = env->event.wheel.y;
	if (env->menu.selected_obj >= 0)
	{
		scale[0] = y / 10.0;
		if (env->rt.objs[env->menu.selected_obj].type == ID_CONE)
			scale[1] = scale[0];
		else
			scale[1] = env->rt.objs[env->menu.selected_obj].scl[1]
					/ env->rt.objs[env->menu.selected_obj].scl[0] * scale[0];
		scale[2] = env->rt.objs[env->menu.selected_obj].scl[2]
				/ env->rt.objs[env->menu.selected_obj].scl[0] * scale[0];
		if (ft_scale_obj(env->rt.objs + env->menu.selected_obj, scale))
		{
			ft_rebuild_objs(env);
			env->param.change = 1;
			env->rt_param.compute = 1;
			env->preview_param.compute = 1;
		}
	}
}
