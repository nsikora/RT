/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeigne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 18:55:03 by ppeigne           #+#    #+#             */
/*   Updated: 2018/06/19 20:07:28 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

void	ft_cpx_copy(const t_cpx c, t_cpx res)
{
	res[C_R] = c[C_R];
	res[C_I] = c[C_I];
}

void	ft_quat_copy(const t_quat q, t_quat res)
{
	res[Q_W] = q[Q_W];
	res[Q_X] = q[Q_X];
	res[Q_Y] = q[Q_Y];
	res[Q_Z] = q[Q_Z];
}

void	ft_vec_copy(const t_vec v, t_quat res)
{
	res[V_X] = v[V_X];
	res[V_Y] = v[V_Y];
	res[V_Z] = v[V_Z];
}

void	ft_mat_copy(const t_mat m, t_mat res)
{
	ft_vec_copy(m[0], res[0]);
	ft_vec_copy(m[1], res[1]);
	ft_vec_copy(m[2], res[2]);
}
