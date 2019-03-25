/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   release_memobjs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeigne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 18:35:41 by ppeigne           #+#    #+#             */
/*   Updated: 2018/08/20 18:35:42 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	ft_release_rt_objs(t_rt_param *param)
{
	clReleaseMemObject(param->mem_objs.mem_obj);
	clReleaseMemObject(param->mem_objs.mem_light);
	clReleaseMemObject(param->mem_objs.mem_tex);
	clReleaseMemObject(param->mem_objs.mem_tab);
	clReleaseMemObject(param->mem_objs.mem_ray);
}

static void	ft_release_post_objs(t_rt_param *param)
{
	clReleaseMemObject(param->mem_objs.mem_post);
	clReleaseMemObject(param->mem_objs.mem_border);
	clReleaseMemObject(param->mem_objs.mem_dir);
}

void		ft_release_all(t_rt_param *param)
{
	ft_release_rt_objs(param);
	ft_release_post_objs(param);
}
