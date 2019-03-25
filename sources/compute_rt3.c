/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_rt3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeigne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 17:43:00 by ppeigne           #+#    #+#             */
/*   Updated: 2018/08/20 17:43:27 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void					ft_compute_rt_light(t_env *env, t_rt_param *param)
{
	if (param->border == 1)
	{
		clEnqueueNDRangeKernel(*env->ocl_rt.queue,
			env->ocl_rt.kernel[K_TOON_LIGHT_ID],
			1, NULL, &param->mem_objs.size, NULL, 0, NULL, NULL);
		clFinish(*env->ocl_rt.queue);
	}
	else
	{
		clEnqueueNDRangeKernel(*env->ocl_rt.queue,
			env->ocl_rt.kernel[K_LIGHT_ID],
			1, NULL, &param->mem_objs.size, NULL, 0, NULL, NULL);
		clFinish(*env->ocl_rt.queue);
	}
}
