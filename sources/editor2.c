/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtheo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 08:36:12 by dtheo             #+#    #+#             */
/*   Updated: 2018/08/21 08:36:14 by dtheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			ft_selector_sliders2(t_env *env)
{
	if (env->menu.trans_val)
		free(env->menu.trans_val);
	env->menu.trans_val = ft_str_percentage(env->menu.trans.val);
	if (env->menu.reflect_val)
		free(env->menu.reflect_val);
	env->menu.reflect_val = ft_str_percentage(env->menu.reflection.val);
	if (env->menu.refract_val)
		free(env->menu.refract_val);
	env->menu.refract_val = ft_ftoa(env->menu.refraction.val, 2);
	if (env->menu.spec_val)
		free(env->menu.spec_val);
	env->menu.spec_val = ft_ftoa(env->menu.spec.val, 2);
	if (env->menu.tex_val)
		free(env->menu.tex_val);
	env->menu.tex_val = ft_name_slider_tex(env);
	if (env->menu.tex_scl_val)
		free(env->menu.tex_scl_val);
	env->menu.tex_scl_val = ft_itoa(floor(env->menu.tex_scl.val));
	env->param.menu_change = 1;
	env->menu.redraw = 1;
}
