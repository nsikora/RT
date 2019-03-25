/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ocl_program_kernel.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeigne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 17:22:17 by ppeigne           #+#    #+#             */
/*   Updated: 2018/08/16 13:43:17 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ocl_framework.h"

static char	*get_program_code(const char *name)
{
	int		fd;
	int		ret;
	char	buff[SIZE + 1];
	char	*tmp;
	char	*source;

	if (!(source = (char *)malloc(sizeof(char) * 1)))
		exit(0);
	source[0] = '\0';
	fd = open(name, O_RDONLY);
	if (fd <= 0)
		ft_putendl("Can't open source file");
	while ((ret = read(fd, buff, SIZE)) > 0)
	{
		buff[ret] = '\0';
		tmp = source;
		source = ft_strjoin(source, buff);
		free(tmp);
	}
	if (ret == -1)
		ft_putendl("Error while reading source file");
	close(fd);
	return (source);
}

static void	program_build_log(t_ocl *ocl, int p_nbr)
{
	char	log[10000];

	if (ocl->ret)
	{
		ocl->ret = clGetProgramBuildInfo(ocl->program[p_nbr], *ocl->d_id,
				CL_PROGRAM_BUILD_LOG, sizeof(char) * 10000, log, NULL);
		ft_putendl(log);
	}
}

void		ft_init_program(t_ocl *ocl, const char **src_name, const int nbr)
{
	int		i;
	size_t	src_size;
	char	**source;

	if (!(source = (char **)malloc(sizeof(char*) * 2)))
		exit(0);
	source[1] = NULL;
	if (!(ocl->program = (cl_program *)malloc(sizeof(cl_program) * nbr)))
		exit(0);
	i = 0;
	while (i < nbr)
	{
		source[0] = get_program_code(src_name[i]);
		src_size = ft_strlen(source[0]);
		ocl->program[i] = clCreateProgramWithSource(ocl->ctxt, 1,
				(const char**)source, (const size_t*)&src_size, &ocl->ret);
		ocl->ret = clBuildProgram(ocl->program[i], 1,
				ocl->d_id, NULL, NULL, NULL);
		program_build_log(ocl, i);
		free(source[0]);
		i++;
	}
	free(source);
}

void		ft_init_kernel(t_ocl *ocl, const char **kernel_name, const int nbr)
{
	int i;

	if (!(ocl->kernel = (cl_kernel *)malloc(sizeof(cl_kernel) * nbr)))
		exit(0);
	i = 0;
	while (i < nbr)
	{
		ocl->kernel[i] = clCreateKernel(ocl->program[i],
				(const char*)kernel_name[i], &ocl->ret);
		if (ocl->ret < 0)
		{
			ft_putendl("Couldn't create any kernels");
			exit(0);
		}
		i++;
	}
}
