/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_arg_postprocess.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeigne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 18:35:50 by ppeigne           #+#    #+#             */
/*   Updated: 2018/08/20 18:35:52 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ft_set_arg_blur(t_env *env, t_rt_param *param)
{
	ft_set_kernel_arg(env->ocl_rt.kernel + K_BLUR_ID, 0, sizeof(int),
				&param->width);
	ft_set_kernel_arg(env->ocl_rt.kernel + K_BLUR_ID, 1, sizeof(int),
				&param->height);
	ft_set_kernel_arg(env->ocl_rt.kernel + K_BLUR_ID, 2, sizeof(cl_mem),
			&param->mem_objs.source);
	ft_set_kernel_arg(env->ocl_rt.kernel + K_BLUR_ID, 3, sizeof(cl_mem),
			&param->mem_objs.mem_post);
}

void		ft_set_arg_greyscale(t_env *env, t_rt_param *param)
{
	(void)param;
	ft_set_kernel_arg(env->ocl_rt.kernel + K_GREYSCALE_ID, 0, sizeof(cl_mem),
		&param->mem_objs.source);
}

void		ft_set_arg_cyan_filter(t_env *env, t_rt_param *param)
{
	int		endian;

	endian = 150;
	ft_set_kernel_arg(env->ocl_rt.kernel + K_CYAN_FILTER_ID, 0, sizeof(cl_mem),
		&param->mem_objs.source);
	ft_set_kernel_arg(env->ocl_rt.kernel + K_CYAN_FILTER_ID, 1, sizeof(int),
		&endian);
}

void		ft_set_arg_color_filter(t_env *env, t_rt_param *param)
{
	int		color;
	int		endian;

	color = param->color;
	endian = 220;
	ft_set_kernel_arg(env->ocl_rt.kernel + K_COLOR_FILTER_ID, 0, sizeof(cl_mem),
		&param->mem_objs.source);
	ft_set_kernel_arg(env->ocl_rt.kernel + K_COLOR_FILTER_ID, 1, sizeof(int),
		&color);
	ft_set_kernel_arg(env->ocl_rt.kernel + K_COLOR_FILTER_ID, 2, sizeof(int),
		&endian);
}

void		ft_set_arg_negative(t_env *env, t_rt_param *param)
{
	ft_set_kernel_arg(env->ocl_rt.kernel + K_NEGATIVE_ID, 0, sizeof(cl_mem),
		&param->mem_objs.source);
}
