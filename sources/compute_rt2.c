/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_rt2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeigne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 18:51:47 by ppeigne           #+#    #+#             */
/*   Updated: 2018/08/20 18:51:49 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_init_rt(t_env *env, t_rt_param *param)
{
	param->mem_objs.size = param->width * param->height;
	ft_set_arg_base(env, param);
	ft_set_arg_ref(env, param);
	ft_set_arg_light(env, param);
}

void	ft_check_stereo(t_rt_param *param)
{
	if (param->stereo == STEREO1)
	{
		param->post = P_COLOR;
		param->color = F_RED;
	}
}

void	ft_stereo(t_env *env, t_rt_param *param)
{
	t_vec move;

	move[0] = 0.5;
	move[1] = 0;
	move[2] = 0;
	if (param->stereo == STEREO1)
	{
		param->lay_dest = param->lay_stereo;
		param->stereo = STEREO2;
		param->post = P_CYAN;
		ft_move(env, move);
		ft_compute_rt(env, param);
		move[0] = -0.5;
		ft_move(env, move);
		env->param.change = 0;
		param->lay_dest = param->lay_rt;
		param->stereo = STEREO1;
		SDL_BlitSurface(param->lay_stereo, NULL, param->lay_rt, NULL);
	}
}

void	ft_compute_rt_ref(t_env *env, t_rt_param *param)
{
	clEnqueueNDRangeKernel(*env->ocl_rt.queue, env->ocl_rt.kernel[K_REF_ID],
		1, NULL, &param->mem_objs.size, NULL, 0, NULL, NULL);
	clFinish(*env->ocl_rt.queue);
	clEnqueueReadBuffer(*env->ocl_rt.queue, param->mem_objs.mem_tab,
			CL_TRUE, 0, sizeof(int) * param->mem_objs.size,
			param->lay_dest->pixels, 0, NULL, NULL);
	clFinish(*env->ocl_rt.queue);
}
