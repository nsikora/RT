/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector2_mag.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtheo <dtheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 16:41:42 by dtheo             #+#    #+#             */
/*   Updated: 2018/05/14 17:35:00 by dtheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double				ft_vector2_mag(t_vector2 v)
{
	double			r;

	r = v.x * v.x;
	r += v.y * v.y;
	r = sqrt(r);
	return (r);
}
