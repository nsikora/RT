/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_release.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeigne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 17:21:04 by ppeigne           #+#    #+#             */
/*   Updated: 2018/08/16 13:39:57 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ocl_framework.h"

void	ft_init_ocl(t_ocl *ocl, const char **p_names,
		const char **k_names, const int nbr)
{
	ft_init_platform(ocl, NO);
	ft_init_device(ocl, CL_DEVICE_TYPE_ALL, NO);
	ocl->ctxt = clCreateContext(NULL, ocl->d_nbr, ocl->d_id,
			NULL, NULL, &ocl->ret);
	ft_init_command_queue(ocl);
	ft_init_program(ocl, p_names, nbr);
	ft_init_kernel(ocl, k_names, nbr);
}

void	ft_release_ocl(t_ocl *ocl)
{
	free(ocl->p_id);
	free(ocl->d_id);
	free(ocl->program);
	free(ocl->kernel);
	free(ocl->queue);
	free(ocl);
}
