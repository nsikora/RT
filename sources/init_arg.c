/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeigne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 17:44:47 by ppeigne           #+#    #+#             */
/*   Updated: 2018/08/20 18:03:39 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				ft_set_arg_base(t_env *env, t_rt_param *param)
{
	ft_set_kernel_arg(env->ocl_rt.kernel + K_RT_ID, 0, sizeof(t_vec_ocl),
			&env->rt.cam_pos);
	ft_set_kernel_arg(env->ocl_rt.kernel + K_RT_ID, 1, sizeof(t_quat),
			&env->rt.cam_rot);
	ft_set_kernel_arg(env->ocl_rt.kernel + K_RT_ID, 2, sizeof(int),
			&param->width);
	ft_set_kernel_arg(env->ocl_rt.kernel + K_RT_ID, 3, sizeof(int),
			&param->height);
	ft_set_kernel_arg(env->ocl_rt.kernel + K_RT_ID, 4, sizeof(t_dec),
			&param->scale);
	ft_set_kernel_arg(env->ocl_rt.kernel + K_RT_ID, 5, sizeof(cl_mem),
			&param->mem_objs.mem_obj);
	ft_set_kernel_arg(env->ocl_rt.kernel + K_RT_ID, 6, sizeof(cl_mem),
			&param->mem_objs.mem_tex);
	ft_set_kernel_arg(env->ocl_rt.kernel + K_RT_ID, 7, sizeof(cl_mem),
			&param->mem_objs.mem_tab);
	ft_set_kernel_arg(env->ocl_rt.kernel + K_RT_ID, 8, sizeof(cl_mem),
			&param->mem_objs.mem_ray);
}

void				ft_set_arg_selector(t_env *env, t_rt_param *param,
					cl_mem *mem_id)
{
	int				x;

	x = env->param.mouse_pos_x - env->menu.rt_rect.x;
	ft_set_kernel_arg(env->ocl_rt.kernel + K_SELECTOR_ID, 0, sizeof(t_vec_ocl),
			&env->rt.cam_pos);
	ft_set_kernel_arg(env->ocl_rt.kernel + K_SELECTOR_ID, 1, sizeof(t_quat),
			&env->rt.cam_rot);
	ft_set_kernel_arg(env->ocl_rt.kernel + K_SELECTOR_ID, 2, sizeof(int),
			&env->rt_param.width);
	ft_set_kernel_arg(env->ocl_rt.kernel + K_SELECTOR_ID, 3, sizeof(int),
			&env->rt_param.height);
	ft_set_kernel_arg(env->ocl_rt.kernel + K_SELECTOR_ID, 4, sizeof(t_dec),
			&env->rt_param.scale);
	ft_set_kernel_arg(env->ocl_rt.kernel + K_SELECTOR_ID, 5, sizeof(cl_mem),
			&param->mem_objs.mem_obj);
	ft_set_kernel_arg(env->ocl_rt.kernel + K_SELECTOR_ID, 6, sizeof(int),
			&x);
	ft_set_kernel_arg(env->ocl_rt.kernel + K_SELECTOR_ID, 7, sizeof(int),
			&env->param.mouse_pos_y);
	ft_set_kernel_arg(env->ocl_rt.kernel + K_SELECTOR_ID, 8,
			sizeof(cl_mem), mem_id);
}

void				ft_set_arg_ref(t_env *env, t_rt_param *param)
{
	int tmp;

	tmp = pow(2, param->r_limit + 1);
	ft_set_kernel_arg(env->ocl_rt.kernel + K_REF_ID, 0, sizeof(t_dec),
			&env->rt_param.ambient);
	ft_set_kernel_arg(env->ocl_rt.kernel + K_REF_ID, 1, sizeof(cl_mem),
			&param->mem_objs.mem_obj);
	ft_set_kernel_arg(env->ocl_rt.kernel + K_REF_ID, 2, sizeof(cl_mem),
			&param->mem_objs.mem_light);
	ft_set_kernel_arg(env->ocl_rt.kernel + K_REF_ID, 3, sizeof(cl_mem),
			&param->mem_objs.mem_tex);
	ft_set_kernel_arg(env->ocl_rt.kernel + K_REF_ID, 4, sizeof(cl_mem),
			&param->mem_objs.mem_tab);
	ft_set_kernel_arg(env->ocl_rt.kernel + K_REF_ID, 5, sizeof(cl_mem),
			&param->mem_objs.mem_ray);
	ft_set_kernel_arg(env->ocl_rt.kernel + K_REF_ID, 6, sizeof(int),
			&param->r_limit);
	ft_set_kernel_arg(env->ocl_rt.kernel + K_REF_ID, 7,
			RAY_SIZE * tmp, NULL);
	ft_set_kernel_arg(env->ocl_rt.kernel + K_REF_ID, 8, sizeof(t_color)
			* (int)fmax(pow(2, param->r_limit) - 2, 2), NULL);
}

void				ft_set_arg_light(t_env *env, t_rt_param *param)
{
	int				i;

	if (param->border == 1)
		i = K_TOON_LIGHT_ID;
	else
		i = K_LIGHT_ID;
	ft_set_kernel_arg(env->ocl_rt.kernel + i, 0, sizeof(t_dec),
			&param->ambient);
	ft_set_kernel_arg(env->ocl_rt.kernel + i, 1, sizeof(cl_mem),
			&param->mem_objs.mem_obj);
	ft_set_kernel_arg(env->ocl_rt.kernel + i, 2, sizeof(cl_mem),
			&param->mem_objs.mem_light);
	ft_set_kernel_arg(env->ocl_rt.kernel + i, 3, sizeof(cl_mem),
			&param->mem_objs.mem_tex);
	ft_set_kernel_arg(env->ocl_rt.kernel + i, 4, sizeof(cl_mem),
			&param->mem_objs.mem_tab);
	ft_set_kernel_arg(env->ocl_rt.kernel + i, 5, sizeof(cl_mem),
			&param->mem_objs.mem_ray);
}
