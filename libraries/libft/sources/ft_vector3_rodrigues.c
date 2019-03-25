/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector3_rodrigues.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtheo <dtheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 04:36:03 by dtheo             #+#    #+#             */
/*   Updated: 2018/05/29 04:36:14 by dtheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vector3		ft_vector3_rodrigues(t_vector3 v, t_vector3 k, double t)
{
	t_vector3	v_r;

	v_r = ft_vector3_scl(v, cos(t));
	v_r = ft_vector3_add(v_r,
		ft_vector3_scl(ft_vector3_cross(k, v), sin(t)));
	v_r = ft_vector3_add(v_r,
		ft_vector3_scl(k, ft_vector3_dot(k, v) * (1 - cos(t))));
	return (v_r);
}
