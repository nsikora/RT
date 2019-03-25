/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_rt_postprocess.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeigne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 18:52:20 by ppeigne           #+#    #+#             */
/*   Updated: 2018/08/20 18:54:31 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				ft_compute_rt_postprocess(t_env *env, t_rt_param *param)
{
	void	(*post_process[5])(t_env *env, t_rt_param *param);

	post_process[0] = ft_compute_rt_blur;
	post_process[1] = ft_compute_rt_greyscale;
	post_process[2] = ft_compute_rt_color_filter;
	post_process[3] = ft_compute_rt_cyan_filter;
	post_process[4] = ft_compute_rt_negative;
	if (param->post == 0)
		return ;
	(*post_process[param->post - 1])(env, param);
	clEnqueueReadBuffer(*env->ocl_rt.queue, param->mem_objs.result,
		CL_TRUE, 0, sizeof(int) * param->mem_objs.size,
		param->lay_dest->pixels, 0, NULL, NULL);
}
