/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_arg_border.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeigne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 18:42:16 by ppeigne           #+#    #+#             */
/*   Updated: 2018/08/20 18:42:18 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				ft_set_arg_sobel(t_env *env, t_rt_param *param)
{
	ft_set_kernel_arg(env->ocl_rt.kernel + K_SOBEL_ID, 0, sizeof(int),
				&param->width);
	ft_set_kernel_arg(env->ocl_rt.kernel + K_SOBEL_ID, 1, sizeof(int),
				&param->height);
	ft_set_kernel_arg(env->ocl_rt.kernel + K_SOBEL_ID, 2, sizeof(cl_mem),
			&param->mem_objs.mem_post);
	ft_set_kernel_arg(env->ocl_rt.kernel + K_SOBEL_ID, 3, sizeof(cl_mem),
			&param->mem_objs.mem_border);
}

void				ft_init_border(t_env *env, t_rt_param *param)
{
	if (param->border == 1)
	{
		param->mem_objs.source = param->mem_objs.mem_tab;
		ft_set_arg_blur(env, param);
		param->mem_objs.source = param->mem_objs.mem_post;
		ft_set_arg_greyscale(env, param);
		ft_set_arg_sobel(env, param);
	}
}
