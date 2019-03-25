/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slider_texture2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtheo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 15:28:33 by dtheo             #+#    #+#             */
/*   Updated: 2018/08/21 15:28:34 by dtheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			ft_event_slider_tex2(t_env *env)
{
	if (env->menu.tex_switch == 0)
	{
		env->menu.last_tex = floor(env->menu.tex.val);
		env->rt.objs[(int)env->menu.selected_obj].texture =
			floor(env->menu.tex.val);
	}
	else if (env->menu.tex_switch == 1)
		env->rt.objs[(int)env->menu.selected_obj].texture_norm =
			floor(env->menu.tex.val);
	else
		env->rt.objs[(int)env->menu.selected_obj].texture_spec =
			floor(env->menu.tex.val);
	if (env->menu.tex_switch != 0)
	{
		ft_rebuild_objs(env);
		env->rt_param.compute = 1;
		env->preview_param.compute = 1;
		env->param.change = 1;
	}
}
