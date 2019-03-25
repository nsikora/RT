/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_arg_antialiasing.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeigne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 18:42:09 by ppeigne           #+#    #+#             */
/*   Updated: 2018/08/20 18:42:11 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	ft_set_arg_sobel_dir(t_env *env, t_rt_param *param)
{
	ft_set_kernel_arg(env->ocl_rt.kernel + K_SOBEL_DIR_ID, 0, sizeof(int),
				&param->width);
	ft_set_kernel_arg(env->ocl_rt.kernel + K_SOBEL_DIR_ID, 1, sizeof(int),
				&param->height);
	ft_set_kernel_arg(env->ocl_rt.kernel + K_SOBEL_DIR_ID, 2, sizeof(cl_mem),
			&param->mem_objs.mem_post);
	ft_set_kernel_arg(env->ocl_rt.kernel + K_SOBEL_DIR_ID, 3, sizeof(cl_mem),
			&param->mem_objs.mem_border);
	ft_set_kernel_arg(env->ocl_rt.kernel + K_SOBEL_DIR_ID, 4, sizeof(cl_mem),
			&param->mem_objs.mem_dir);
}

static void	ft_set_arg_canny(t_env *env, t_rt_param *param)
{
	ft_set_kernel_arg(env->ocl_rt.kernel + K_CANNY_ID, 0, sizeof(int),
				&param->width);
	ft_set_kernel_arg(env->ocl_rt.kernel + K_CANNY_ID, 1, sizeof(int),
				&param->height);
	ft_set_kernel_arg(env->ocl_rt.kernel + K_CANNY_ID, 2, sizeof(cl_mem),
			&param->mem_objs.mem_border);
	ft_set_kernel_arg(env->ocl_rt.kernel + K_CANNY_ID, 3, sizeof(cl_mem),
			&param->mem_objs.mem_dir);
}

void		ft_set_arg_antialiasing(t_env *env, t_rt_param *param)
{
	ft_set_kernel_arg(env->ocl_rt.kernel + K_ANTIALIASING_ID, 0, sizeof(int),
				&param->width);
	ft_set_kernel_arg(env->ocl_rt.kernel + K_ANTIALIASING_ID, 1, sizeof(int),
				&param->height);
	ft_set_kernel_arg(env->ocl_rt.kernel + K_ANTIALIASING_ID, 2, sizeof(cl_mem),
			&param->mem_objs.mem_tab);
	ft_set_kernel_arg(env->ocl_rt.kernel + K_ANTIALIASING_ID, 3, sizeof(cl_mem),
			&param->mem_objs.mem_border);
	ft_set_kernel_arg(env->ocl_rt.kernel + K_ANTIALIASING_ID, 4, sizeof(cl_mem),
			&param->mem_objs.mem_post);
}

void		ft_init_antialiasing(t_env *env, t_rt_param *param)
{
	if (param->border == 2)
	{
		param->mem_objs.source = param->mem_objs.mem_tab;
		ft_set_arg_blur(env, param);
		param->mem_objs.source = param->mem_objs.mem_post;
		ft_set_arg_greyscale(env, param);
		ft_set_arg_sobel_dir(env, param);
		ft_set_arg_canny(env, param);
		ft_set_arg_antialiasing(env, param);
	}
}
