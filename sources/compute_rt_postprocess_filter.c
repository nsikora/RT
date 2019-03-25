/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_rt_postprocess_filter.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeigne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 18:54:42 by ppeigne           #+#    #+#             */
/*   Updated: 2018/08/20 18:54:44 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				ft_compute_rt_blur(t_env *env, t_rt_param *param)
{
	clEnqueueNDRangeKernel(*env->ocl_rt.queue, env->ocl_rt.kernel[K_BLUR_ID],
		1, NULL, &param->mem_objs.size, NULL, 0, NULL, NULL);
	clFinish(*env->ocl_rt.queue);
	param->mem_objs.result = param->mem_objs.mem_post;
}

void				ft_compute_rt_greyscale(t_env *env, t_rt_param *param)
{
	clEnqueueNDRangeKernel(*env->ocl_rt.queue,
		env->ocl_rt.kernel[K_GREYSCALE_ID], 1, NULL,
		&param->mem_objs.size, NULL, 0, NULL, NULL);
	clFinish(*env->ocl_rt.queue);
	param->mem_objs.result = param->mem_objs.mem_tab;
}

void				ft_compute_rt_negative(t_env *env, t_rt_param *param)
{
	clEnqueueNDRangeKernel(*env->ocl_rt.queue,
			env->ocl_rt.kernel[K_NEGATIVE_ID],
			1, NULL, &param->mem_objs.size, NULL, 0, NULL, NULL);
	clFinish(*env->ocl_rt.queue);
	param->mem_objs.result = param->mem_objs.mem_tab;
}

void				ft_compute_rt_color_filter(t_env *env, t_rt_param *param)
{
	clEnqueueNDRangeKernel(*env->ocl_rt.queue,
			env->ocl_rt.kernel[K_COLOR_FILTER_ID],
			1, NULL, &param->mem_objs.size, NULL, 0, NULL, NULL);
	clFinish(*env->ocl_rt.queue);
	param->mem_objs.result = param->mem_objs.mem_tab;
}

void				ft_compute_rt_cyan_filter(t_env *env, t_rt_param *param)
{
	clEnqueueNDRangeKernel(*env->ocl_rt.queue,
		env->ocl_rt.kernel[K_CYAN_FILTER_ID], 1, NULL,
		&param->mem_objs.size, NULL, 0, NULL, NULL);
	clFinish(*env->ocl_rt.queue);
	param->mem_objs.result = param->mem_objs.mem_tab;
}
