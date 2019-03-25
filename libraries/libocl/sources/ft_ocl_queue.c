/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ocl_queue.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeigne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 17:23:34 by ppeigne           #+#    #+#             */
/*   Updated: 2018/08/16 13:43:27 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ocl_framework.h"

void	ft_init_command_queue(t_ocl *ocl)
{
	unsigned int i;

	if (!(ocl->queue = ft_memalloc(sizeof(cl_command_queue) * ocl->d_nbr)))
		exit(0);
	i = 0;
	while (i < ocl->d_nbr)
	{
		ocl->queue[i] = clCreateCommandQueue(ocl->ctxt, ocl->d_id[i], 0,
				&ocl->ret);
		i++;
	}
}
