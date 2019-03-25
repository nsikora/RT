/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_rt_border.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeigne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 18:52:07 by ppeigne           #+#    #+#             */
/*   Updated: 2018/08/20 18:52:10 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				ft_compute_rt_sobel(t_env *env, t_rt_param *param)
{
	clEnqueueNDRangeKernel(*env->ocl_rt.queue, env->ocl_rt.kernel[K_SOBEL_ID],
			1, NULL, &param->mem_objs.size, NULL, 0, NULL, NULL);
	clFinish(*env->ocl_rt.queue);
}

void				ft_compute_rt_border(t_env *env, t_rt_param *param)
{
	if (param->border == 1)
	{
		ft_compute_rt_blur(env, param);
		ft_compute_rt_greyscale(env, param);
		ft_compute_rt_sobel(env, param);
		clEnqueueReadBuffer(*env->ocl_rt.queue, param->mem_objs.mem_border,
			CL_TRUE, 0, sizeof(int) * param->mem_objs.size,
		param->lay_border->pixels, 0, NULL, NULL);
	}
}
