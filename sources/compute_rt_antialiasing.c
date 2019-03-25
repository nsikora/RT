/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_rt_antialiasing.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeigne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 18:52:29 by ppeigne           #+#    #+#             */
/*   Updated: 2018/08/20 18:52:30 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				ft_compute_rt_sobel_dir(t_env *env, t_rt_param *param)
{
	clEnqueueNDRangeKernel(*env->ocl_rt.queue,
			env->ocl_rt.kernel[K_SOBEL_DIR_ID],
			1, NULL, &param->mem_objs.size, NULL, 0, NULL, NULL);
	clFinish(*env->ocl_rt.queue);
}

void				ft_compute_rt_canny(t_env *env, t_rt_param *param)
{
	clEnqueueNDRangeKernel(*env->ocl_rt.queue, env->ocl_rt.kernel[K_CANNY_ID],
			1, NULL, &param->mem_objs.size, NULL, 0, NULL, NULL);
	clFinish(*env->ocl_rt.queue);
}

void				ft_compute_rt_edges_blur(t_env *env, t_rt_param *param)
{
	clEnqueueNDRangeKernel(*env->ocl_rt.queue,
			env->ocl_rt.kernel[K_ANTIALIASING_ID],
			1, NULL, &param->mem_objs.size, NULL, 0, NULL, NULL);
	clFinish(*env->ocl_rt.queue);
}

void				ft_compute_rt_antialiasing(t_env *env, t_rt_param *param)
{
	if (param->border == 2)
	{
		ft_compute_rt_blur(env, param);
		ft_compute_rt_greyscale(env, param);
		ft_compute_rt_sobel_dir(env, param);
		ft_compute_rt_canny(env, param);
		ft_compute_rt_edges_blur(env, param);
		clEnqueueReadBuffer(*env->ocl_rt.queue, param->mem_objs.mem_post,
			CL_TRUE, 0, sizeof(int) * param->mem_objs.size,
		param->lay_rt->pixels, 0, NULL, NULL);
	}
}
