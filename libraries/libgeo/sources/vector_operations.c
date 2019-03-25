/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeigne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 17:53:21 by ppeigne           #+#    #+#             */
/*   Updated: 2018/06/19 19:13:59 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

void	ft_sub_vec(const t_vec v0, const t_vec v1, t_vec res)
{
	res[V_X] = v0[V_X] - v1[V_X];
	res[V_Y] = v0[V_Y] - v1[V_Y];
	res[V_Z] = v0[V_Z] - v1[V_Z];
}

void	ft_add_vec(const t_vec v0, const t_vec v1, t_vec res)
{
	res[V_X] = v0[V_X] + v1[V_X];
	res[V_Y] = v0[V_Y] + v1[V_Y];
	res[V_Z] = v0[V_Z] + v1[V_Z];
}

void	ft_scalar_mult(const t_vec v, const t_dec scalar, t_vec res)
{
	res[V_X] = scalar * v[V_X];
	res[V_Y] = scalar * v[V_Y];
	res[V_Z] = scalar * v[V_Z];
}

t_dec	ft_dot_product(const t_vec v0, const t_vec v1)
{
	return (v0[V_X] * v1[V_X] + v0[V_Y] * v1[V_Y] + v0[V_Z] * v1[V_Z]);
}

void	ft_cross_product(const t_vec v0, const t_vec v1, t_vec product)
{
	product[V_X] = v0[V_Y] * v1[V_Z] - v0[V_Z] * v1[V_Y];
	product[V_Y] = v0[V_Z] * v1[V_X] - v0[V_X] * v1[V_Z];
	product[V_Z] = v0[V_X] * v1[V_Y] - v0[V_Y] * v1[V_X];
}
