/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ocl_platform.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeigne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 17:22:05 by ppeigne           #+#    #+#             */
/*   Updated: 2018/08/16 13:42:48 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ocl_framework.h"

static void		platform_extensions(cl_platform_id p_id)
{
	char		**ext;
	char		info[512];
	size_t		size;

	clGetPlatformInfo(p_id, CL_PLATFORM_EXTENSIONS, sizeof(info),
			info, &size);
	ft_putstr("\n - PLATFORM EXTENSIONS:\n");
	ext = ft_strsplit(info, ' ');
	while (*ext)
	{
		ft_putchar('\t');
		ft_putendl(*ext);
		ext++;
	}
}

void			ft_platform_info(cl_platform_id p_id)
{
	char		info[512];
	size_t		size;

	ft_putendl("PLATFORM'S INFORMATIONS:\n");
	clGetPlatformInfo(p_id, CL_PLATFORM_NAME, sizeof(info),
			info, &size);
	ft_putstr(" - PLATFORM'S NAME:\n\t");
	ft_putendl(info);
	clGetPlatformInfo(p_id, CL_PLATFORM_VENDOR, sizeof(info),
			info, &size);
	ft_putstr("\n - PLATFORM'S VENDOR:\n\t");
	ft_putendl(info);
	clGetPlatformInfo(p_id, CL_PLATFORM_VERSION, sizeof(info),
			info, &size);
	ft_putstr("\n - PLATFORM'S VERSION:\n\t");
	ft_putendl(info);
	clGetPlatformInfo(p_id, CL_PLATFORM_PROFILE, sizeof(info),
			info, &size);
	ft_putstr("\n - PLATFORM'S PROFILE:\n\t");
	ft_putendl(info);
	platform_extensions(p_id);
}

void			ft_init_platform(t_ocl *ocl, int info)
{
	cl_uint		nb_plat;

	ocl->ret = clGetPlatformIDs(2000, NULL, &nb_plat);
	if (!(ocl->p_id = (cl_platform_id *)ft_memalloc(sizeof(cl_platform_id)
					* nb_plat)))
		exit(1);
	ocl->ret = clGetPlatformIDs(nb_plat, ocl->p_id, NULL);
	if (info > 0)
	{
		ft_putnbr(nb_plat);
		ft_putendl(" platforms.");
		while (nb_plat--)
			ft_platform_info(ocl->p_id[nb_plat]);
	}
}
