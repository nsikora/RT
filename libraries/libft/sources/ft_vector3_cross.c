/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector3_cross.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtheo <dtheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 16:23:09 by dtheo             #+#    #+#             */
/*   Updated: 2018/05/14 16:24:31 by dtheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vector3			ft_vector3_cross(t_vector3 u, t_vector3 v)
{
	t_vector3		r;

	r.x = u.y * v.z - u.z * v.y;
	r.y = u.z * v.x - u.x * v.z;
	r.z = u.x * v.y - u.y * v.x;
	return (r);
}
