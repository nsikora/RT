/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion_operations.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeigne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 18:09:06 by ppeigne           #+#    #+#             */
/*   Updated: 2018/08/20 13:56:03 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

void	ft_add_quat(const t_quat q1, const t_quat q2, t_quat res)
{
	res[Q_W] = q1[Q_W] + q2[Q_W];
	res[Q_X] = q1[Q_X] + q2[Q_X];
	res[Q_Y] = q1[Q_Y] + q2[Q_Y];
	res[Q_Z] = q1[Q_Z] + q2[Q_Z];
}

void	ft_sub_quat(const t_quat q1, const t_quat q2, t_quat res)
{
	res[Q_W] = q1[Q_W] - q2[Q_W];
	res[Q_X] = q1[Q_X] - q2[Q_X];
	res[Q_Y] = q1[Q_Y] - q2[Q_Y];
	res[Q_Z] = q1[Q_Z] - q2[Q_Z];
}

/*
** q1 * q2 = (w1*w2 - v1 dot v2, w1*v2 + w2*v1 + v1 cros v2)
*/
/*
**void	ft_quat_mult(const t_quat q1, const t_quat q2, t_quat res)
**{
**	t_vec	tmp1;
**	t_vec	tmp2;
**	t_vec	tmp;
**	t_vec	cros;
**
**	ft_vec_copy(q1 + 1, tmp1);
**	ft_vec_copy(q2 + 1, tmp2);
**	res[Q_W] = q1[Q_W] * q2[Q_W] - ft_dot_product(q1 + 1, q2 + 1);
**	ft_scalar_mult(tmp1, q2[Q_W], tmp1);
**	ft_scalar_mult(tmp2, q1[Q_W], tmp2);
**	ft_cross_product(q1, q2, cros);
**	ft_add_vec(tmp1, tmp2, tmp);
**	ft_add_vec(tmp, cros, res + 1);
**}
*/
/*
** Be carefull ! q1 * q2 != q2 * q1
*/

void	ft_quat_mult(const t_quat q1, const t_quat q2, t_quat res)
{
	t_dec	m_q1[4][4];

	ft_quat_to_mat(q1, m_q1);
	ft_mat_quat_mult(m_q1, q2, res);
}

void	ft_init_quat_with_rot(const t_vec rot, t_quat res)
{
	t_quat			tmp1;
	t_quat			tmp2;
	t_quat			tmp3;

	ft_vec_to_quat((t_vec){1, 0, 0}, rot[V_X], tmp1);
	ft_vec_to_quat((t_vec){0, 1, 0}, rot[V_Y], tmp2);
	ft_quat_mult(tmp1, tmp2, tmp3);
	ft_vec_to_quat((t_vec){0, 0, 1}, rot[V_Z], tmp1);
	ft_quat_mult(tmp1, tmp3, res);
}
