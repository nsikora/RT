/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ocl_device.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeigne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 17:21:18 by ppeigne           #+#    #+#             */
/*   Updated: 2018/06/25 18:09:07 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ocl_framework.h"

static void	device_basic_info(cl_device_id d_id)
{
	char			info[512];
	cl_device_type	type;

	type = 0;
	clGetDeviceInfo(d_id, CL_DEVICE_NAME, sizeof(info), info, NULL);
	ft_putstr(" - DEVICE'S NAME:\n\t");
	ft_putendl(info);
	clGetDeviceInfo(d_id, CL_DEVICE_TYPE, sizeof(type), &type, NULL);
	ft_putstr(" - DEVICE'S TYPE:\n\t");
	if (type == CL_DEVICE_TYPE_CPU)
		ft_putendl("CL_DEVICE_TYPE_CPU");
	else if (type == CL_DEVICE_TYPE_GPU)
		ft_putendl("CL_DEVICE_TYPE_GPU");
	else if (type == CL_DEVICE_TYPE_ACCELERATOR)
		ft_putendl("CL_DEVICE_TYPE_ACCELERATOR");
	else
		ft_putendl("CL_DEVICE_TYPE_DEFAULT");
	clGetDeviceInfo(d_id, CL_DEVICE_VENDOR, sizeof(info), info, NULL);
	ft_putstr(" - DEVICE'S VENDOR:\n\t");
	ft_putendl(info);
	clGetDeviceInfo(d_id, CL_DEVICE_VERSION, sizeof(info), info, NULL);
	ft_putstr(" - DEVICE'S VERSION:\n\t");
	ft_putendl(info);
}

static void	device_work_info(cl_device_id d_id)
{
	size_t	size;
	size_t	*val_dim;
	size_t	i;

	size = 0;
	clGetDeviceInfo(d_id, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(size), &size,
			NULL);
	ft_putstr(" - DEVICE'S MAXIMUM WORK GROUP SIZE:\n\t");
	ft_putnbr(size);
	clGetDeviceInfo(d_id, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, sizeof(size),
			&size, NULL);
	ft_putstr("\n - DEVICE'S MAXIMUM WORK ITEM DIMENSIONS:\n\t");
	ft_putnbr(size);
	clGetDeviceInfo(d_id, CL_DEVICE_MAX_WORK_ITEM_SIZES, 0, NULL, &size);
	val_dim = malloc(size);
	clGetDeviceInfo(d_id, CL_DEVICE_MAX_WORK_ITEM_SIZES,
			size, val_dim, NULL);
	ft_putstr("\n - DEVICE'S MAXIMUM WORK ITEM SIZES:\n\t");
	i = -1;
	while (++i < 3)
	{
		ft_putnbr(val_dim[i]);
		ft_putstr("  ");
	}
	ft_putchar('\n');
}

static void	device_memory_info(cl_device_id d_id)
{
	cl_ulong	mem;

	clGetDeviceInfo(d_id, CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(mem),
			&mem, NULL);
	ft_putstr(" - DEVICE'S GLOBAL MEMORY SIZE:\n\t");
	ft_putnbr(mem / (1024 * 1024));
	clGetDeviceInfo(d_id, CL_DEVICE_GLOBAL_MEM_CACHE_SIZE, sizeof(mem),
			&mem, NULL);
	ft_putstr(" Mo\n - DEVICE'S GLOBAL MEMORY CACHE SIZE:\n\t");
	ft_putnbr(mem);
	clGetDeviceInfo(d_id, CL_DEVICE_LOCAL_MEM_SIZE, sizeof(mem),
			&mem, NULL);
	ft_putstr(" Bytes\n - DEVICE'S LOCAL MEMORY CACHE SIZE:\n\t");
	ft_putnbr(mem / (1024));
	clGetDeviceInfo(d_id, CL_DEVICE_MAX_MEM_ALLOC_SIZE, sizeof(mem),
			&mem, NULL);
	ft_putstr(" Ko\n - DEVICE'S MAXIMUM MEMORY ALLOCATION SIZE:\n\t");
	ft_putnbr(mem / (1024 * 1024));
	clGetDeviceInfo(d_id, CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE, sizeof(mem),
			&mem, NULL);
	ft_putstr(" Mo\n - DEVICE'S MAXIMUM CONSTANT BUFFER SIZE:\n\t");
	ft_putnbr(mem / (1024));
	ft_putstr(" Ko");
}

static void	device_diverse_info(cl_device_id d_id)
{
	cl_uint	val;
	char	info[512];
	char	**ext;

	clGetDeviceInfo(d_id, CL_DEVICE_MAX_CONSTANT_ARGS, sizeof(val),
			&val, NULL);
	ft_putstr("\n - DEVICE'S MAXIMUM CONSTANT ARGUMENTS:\n\t");
	ft_putnbr(val);
	clGetDeviceInfo(d_id, CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT,
			sizeof(val), &val, NULL);
	ft_putstr("\n - DEVICE'S PREFERED VECTOR WITH FLOAT:\n\t");
	ft_putnbr(val);
	clGetDeviceInfo(d_id, CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE,
			sizeof(val), &val, NULL);
	ft_putstr("\n - DEVICE'S PREFERED VECTOR WITH DOUBLE:\n\t");
	ft_putnbr(val);
	clGetDeviceInfo(d_id, CL_DEVICE_EXTENSIONS, sizeof(info), info, NULL);
	ft_putstr("\n - DEVICE'S EXTENSIONS:\n");
	ext = ft_strsplit(info, ' ');
	while (*ext)
	{
		ft_putchar('\t');
		ft_putendl(*ext);
		ext++;
	}
}

void		ft_device_info(cl_device_id *d_id, const int nb_d)
{
	int	i;

	i = -1;
	ft_putendl("DEVICE(S)'S INFORMATIONS:");
	while (d_id[++i] && i < nb_d)
	{
		ft_putstr("\n - DEVICE'S ID:\n\t");
		ft_putnbr(i);
		ft_putchar('\n');
		device_basic_info(d_id[i]);
		device_work_info(d_id[i]);
		device_memory_info(d_id[i]);
		device_diverse_info(d_id[i]);
	}
}
