/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ocl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeigne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 18:42:37 by ppeigne           #+#    #+#             */
/*   Updated: 2018/08/20 18:42:42 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	ft_free_ocl(char **name, char **path, t_ocl *ocl)
{
	int i;

	i = -1;
	while (++i < K_TOTAL + 1)
	{
		free(name[i]);
		free(path[i]);
	}
	free(name);
	free(path);
	free(ocl->p_id);
	free(ocl->d_id);
	free(ocl->program);
}

static char	**init_kernel_path(t_env *env)
{
	char	**k_path;

	if (!(k_path = (char **)ft_memalloc(sizeof(char *) * (K_TOTAL + 1))))
		ft_malloc_error(env);
	k_path[K_RT_ID] = ft_strdup(K_RT_PATH);
	k_path[K_REF_ID] = ft_strdup(K_REF_PATH);
	k_path[K_LIGHT_ID] = ft_strdup(K_LIGHT_PATH);
	k_path[K_BLUR_ID] = ft_strdup(K_BLUR_PATH);
	k_path[K_GREYSCALE_ID] = ft_strdup(K_GREYSCALE_PATH);
	k_path[K_SOBEL_ID] = ft_strdup(K_SOBEL_PATH);
	k_path[K_TOON_LIGHT_ID] = ft_strdup(K_TOON_LIGHT_PATH);
	k_path[K_COLOR_FILTER_ID] = ft_strdup(K_COLOR_FILTER_PATH);
	k_path[K_CYAN_FILTER_ID] = ft_strdup(K_CYAN_FILTER_PATH);
	k_path[K_NEGATIVE_ID] = ft_strdup(K_NEGATIVE_PATH);
	k_path[K_SOBEL_DIR_ID] = ft_strdup(K_SOBEL_DIR_PATH);
	k_path[K_CANNY_ID] = ft_strdup(K_CANNY_PATH);
	k_path[K_ANTIALIASING_ID] = ft_strdup(K_ANTIALIASING_PATH);
	k_path[K_SELECTOR_ID] = ft_strdup(K_SELECTOR_PATH);
	k_path[K_TOTAL] = NULL;
	return (k_path);
}

static char	**init_kernel_name(t_env *env)
{
	char	**k_name;

	if (!(k_name = (char **)ft_memalloc(sizeof(char *) * (K_TOTAL + 1))))
		ft_malloc_error(env);
	k_name[K_RT_ID] = ft_strdup(K_RT_NAME);
	k_name[K_REF_ID] = ft_strdup(K_REF_NAME);
	k_name[K_LIGHT_ID] = ft_strdup(K_LIGHT_NAME);
	k_name[K_BLUR_ID] = ft_strdup(K_BLUR_NAME);
	k_name[K_GREYSCALE_ID] = ft_strdup(K_GREYSCALE_NAME);
	k_name[K_SOBEL_ID] = ft_strdup(K_SOBEL_NAME);
	k_name[K_TOON_LIGHT_ID] = ft_strdup(K_TOON_LIGHT_NAME);
	k_name[K_COLOR_FILTER_ID] = ft_strdup(K_COLOR_FILTER_NAME);
	k_name[K_CYAN_FILTER_ID] = ft_strdup(K_CYAN_FILTER_NAME);
	k_name[K_NEGATIVE_ID] = ft_strdup(K_NEGATIVE_NAME);
	k_name[K_SOBEL_DIR_ID] = ft_strdup(K_SOBEL_DIR_NAME);
	k_name[K_CANNY_ID] = ft_strdup(K_CANNY_NAME);
	k_name[K_ANTIALIASING_ID] = ft_strdup(K_ANTIALIASING_NAME);
	k_name[K_SELECTOR_ID] = ft_strdup(K_SELECTOR_NAME);
	k_name[K_TOTAL] = NULL;
	return (k_name);
}

void		ft_init_ocl_param(t_env *env)
{
	char	**k_path;
	char	**k_name;
	t_ocl	ocl;

	k_path = init_kernel_path(env);
	k_name = init_kernel_name(env);
	ft_init_ocl(&ocl, (const char **)k_path, (const char **)k_name, K_TOTAL);
	env->ocl_rt.context = ocl.ctxt;
	env->ocl_rt.kernel = ocl.kernel;
	env->ocl_rt.queue = ocl.queue;
	ft_free_ocl(k_path, k_name, &ocl);
}
