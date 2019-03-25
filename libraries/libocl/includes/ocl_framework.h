/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl_framework.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeigne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 15:00:28 by ppeigne           #+#    #+#             */
/*   Updated: 2018/06/25 18:07:49 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OCL_FRAMEWORK_H
# define OCL_FRAMEWORK_H

# include <stdlib.h>
# include <string.h>
# include "libft.h"

# define CL_USE_DEPRECATED_OPENCL_1_2_APIS

# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# else
#  include <CL/cl.h>
# endif

# define SIZE 32
# define NO 0
# define YES 1
# define FULL 2

typedef	struct			s_ocl
{
	cl_platform_id		*p_id;
	cl_device_id		*d_id;
	cl_context			ctxt;
	cl_program			*program;
	cl_kernel			*kernel;
	cl_command_queue	*queue;
	cl_uint				p_nbr;
	cl_uint				d_nbr;
	cl_int				ret;
	cl_bool				available;
}						t_ocl;

void					ft_init_ocl(t_ocl *ocl, const char **p_names,
						const char **k_names, const int nbr);
void					ft_release_ocl(t_ocl *ocl);

void					ft_init_platform(t_ocl *ocl, int info);
void					ft_platform_info(cl_platform_id p_id);

void					ft_init_device(t_ocl *ocl, const cl_device_type type,
						int info);

void					ft_device_info(cl_device_id *d_id, const int d_nb);

void					ft_init_program(t_ocl *ocl, const char **s_name,
						const int nbr);

void					ft_init_kernel(t_ocl *ocl, const char **k_name,
						const int nbr);

void					ft_init_command_queue(t_ocl *ocl);

void					ft_ocl_init_error(const int ret);

void					ft_ocl_kernel_error(const int ret, const size_t index);

void					ft_set_kernel_arg(cl_kernel *kernel, size_t index,
						size_t size, void *mem);
#endif
