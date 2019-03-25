/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_arg_postprocess.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeigne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 18:42:22 by ppeigne           #+#    #+#             */
/*   Updated: 2018/08/20 18:42:24 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ft_init_postprocess(t_env *env, t_rt_param *param)
{
	void	(*set_postprocess_arg[5])(t_env *env, t_rt_param *param);

	set_postprocess_arg[0] = ft_set_arg_blur;
	set_postprocess_arg[1] = ft_set_arg_greyscale;
	set_postprocess_arg[2] = ft_set_arg_color_filter;
	set_postprocess_arg[3] = ft_set_arg_cyan_filter;
	set_postprocess_arg[4] = ft_set_arg_negative;
	param->mem_objs.source = param->mem_objs.mem_tab;
	if (param->post == 0)
		return ;
	(*set_postprocess_arg[param->post - 1])(env, param);
}
