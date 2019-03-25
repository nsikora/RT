/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_nb_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsikora <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 15:01:46 by nsikora           #+#    #+#             */
/*   Updated: 2018/08/21 15:08:08 by nsikora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	put_nb_error(t_env *env)
{
	if (env->rt_param.mem_objs.nb_obj == 1)
		ft_error("Error: No Raytracer object in this file. End of programm");
	if (env->preview_param.mem_objs.nb_tex > 10)
		ft_error("Error: Too many textures loaded at once. Cap is set at 10");
}
