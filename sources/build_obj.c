/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeigne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 18:51:57 by ppeigne           #+#    #+#             */
/*   Updated: 2018/08/20 18:51:59 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ft_build_mem_obj(t_env *env, t_rt_param *param)
{
	param->mem_objs.mem_obj = clCreateBuffer(env->ocl_rt.context,
		CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
		sizeof(t_obj) * param->mem_objs.nb_obj, env->rt.objs, NULL);
}

void		ft_build_mem_light(t_env *env, t_rt_param *param)
{
	param->mem_objs.mem_light = clCreateBuffer(env->ocl_rt.context,
			CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
			sizeof(t_light) * param->mem_objs.nb_light, env->rt.lights, NULL);
}

void		ft_build_mem_tex(t_env *env, t_rt_param *param)
{
	param->mem_objs.mem_tex = clCreateBuffer(env->ocl_rt.context,
			CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
			sizeof(t_tex) * param->mem_objs.nb_tex, env->rt.textures, NULL);
}

void		ft_build_obj_rt(t_env *env, t_rt_param *param)
{
	param->mem_objs.size = param->width * param->height;
	ft_build_mem_obj(env, param);
	ft_build_mem_light(env, param);
	ft_build_mem_tex(env, param);
	param->mem_objs.mem_tab = clCreateBuffer(env->ocl_rt.context,
			CL_MEM_READ_WRITE, sizeof(t_color) * param->mem_objs.size,
			NULL, NULL);
	param->mem_objs.mem_ray = clCreateBuffer(env->ocl_rt.context,
			CL_MEM_READ_WRITE, RAY_SIZE * param->mem_objs.size,
			NULL, NULL);
	param->mem_objs.mem_post = clCreateBuffer(env->ocl_rt.context,
			CL_MEM_READ_WRITE, sizeof(t_color) * param->mem_objs.size,
			NULL, NULL);
	param->mem_objs.mem_border = clCreateBuffer(env->ocl_rt.context,
			CL_MEM_READ_WRITE, sizeof(t_color) * param->mem_objs.size,
			NULL, NULL);
	param->mem_objs.mem_dir = clCreateBuffer(env->ocl_rt.context,
			CL_MEM_READ_WRITE, sizeof(float) * param->mem_objs.size,
			NULL, NULL);
}

void		ft_rebuild_objs(t_env *env)
{
	clReleaseMemObject(env->rt_param.mem_objs.mem_obj);
	ft_build_mem_obj(env, &env->rt_param);
	clReleaseMemObject(env->preview_param.mem_objs.mem_obj);
	ft_build_mem_obj(env, &env->preview_param);
}
