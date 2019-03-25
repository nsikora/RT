/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion_compute.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeigne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 18:08:56 by ppeigne           #+#    #+#             */
/*   Updated: 2018/06/20 17:05:25 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

void	ft_quat_to_power(const t_quat q, int power, t_quat result)
{
	ft_quat_mult(q, q, result);
	power--;
	while (power > 1)
	{
		ft_quat_mult(result, q, result);
		power--;
	}
}

/*
** [a, b, c, d] =
**
** [ a][-b][-c][-d]
** [ b][ a][-d][ c]
** [ c][ d][ a][-b]
** [ d][-c][ b][ a]
*/

void	ft_quat_to_mat(const t_quat q, t_dec mat[4][4])
{
	mat[0][0] = q[0];
	mat[0][1] = -q[1];
	mat[0][2] = -q[2];
	mat[0][3] = -q[3];
	mat[1][0] = q[1];
	mat[1][1] = q[0];
	mat[1][2] = -q[3];
	mat[1][3] = q[2];
	mat[2][0] = q[2];
	mat[2][1] = q[3];
	mat[2][2] = q[0];
	mat[2][3] = -q[1];
	mat[3][0] = q[3];
	mat[3][1] = -q[2];
	mat[3][2] = q[1];
	mat[3][3] = q[0];
}

void	ft_mat_quat_mult(const t_dec mat[4][4], const t_quat quat, t_quat res)
{
	int		row;
	t_quat	tmp;

	row = 0;
	while (row < 4)
	{
		tmp[row] = quat[0] * mat[row][0] + quat[1] * mat[row][1]
			+ quat[2] * mat[row][2] + quat[3] * mat[row][3];
		row++;
	}
	ft_quat_copy(tmp, res);
}
