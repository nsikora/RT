/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector3_dot.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtheo <dtheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 16:19:27 by dtheo             #+#    #+#             */
/*   Updated: 2018/05/14 16:20:46 by dtheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double				ft_vector3_dot(t_vector3 u, t_vector3 v)
{
	double			r;

	r = u.x * v.x;
	r += u.y * v.y;
	r += u.z * v.z;
	return (r);
}