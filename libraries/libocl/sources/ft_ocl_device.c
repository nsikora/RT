/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ocl_device.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeigne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 17:21:18 by ppeigne           #+#    #+#             */
/*   Updated: 2018/08/16 13:38:50 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ocl_framework.h"

void		ft_init_device(t_ocl *ocl, const cl_device_type type, int info)
{
	ocl->ret = clGetDeviceIDs(ocl->p_id[0], type, 1, NULL, &ocl->d_nbr);
	if (!(ocl->d_id = (cl_device_id*)malloc(sizeof(cl_device_id) * ocl->d_nbr)))
		exit(0);
	ocl->ret = clGetDeviceIDs(ocl->p_id[0], type, ocl->d_nbr, ocl->d_id, NULL);
	if (info > 0)
		ft_device_info(ocl->d_id, ocl->d_nbr);
}
