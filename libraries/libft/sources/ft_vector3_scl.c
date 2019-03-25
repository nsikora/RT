/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector3_scl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtheo <dtheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 16:20:56 by dtheo             #+#    #+#             */
/*   Updated: 2018/05/14 16:21:39 by dtheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vector3			ft_vector3_scl(t_vector3 v, double s)
{
	v.x *= s;
	v.y *= s;
	v.z *= s;
	return (v);
}