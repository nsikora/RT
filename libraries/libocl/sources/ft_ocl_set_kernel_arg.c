/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ocl_set_kernel_arg.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeigne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 17:29:11 by ppeigne           #+#    #+#             */
/*   Updated: 2018/08/16 13:44:04 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ocl_framework.h"

void	ft_set_kernel_arg(cl_kernel *kernel, size_t index,
		size_t size, void *mem)
{
	cl_int	error;

	error = clSetKernelArg(*kernel, index, size, mem);
	ft_ocl_kernel_error(error, index);
}
