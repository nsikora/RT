/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_compute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeigne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 16:23:08 by ppeigne           #+#    #+#             */
/*   Updated: 2018/06/21 16:37:28 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

/*
**  rot_x(th):
**  [ 1 ]	[ 0 ]	   [ 0 ]
**  [ 0 ] [cos(th)]  [sin(th)]
**  [ 0 ] [-sin(th)] [cos(th)]
*/

void		ft_x_rotation(const t_dec angle, t_mat m_rot)
{
	t_mat	mat;
	t_mat	mat_cpy;
	t_dec	th;

	if (angle == 0)
		return ;
	th = ft_deg_to_rad(angle);
	ft_set_identity(mat);
	ft_mat_copy(m_rot, mat_cpy);
	mat[1][1] = cos(th);
	mat[1][2] = sin(th);
	mat[2][1] = -sin(th);
	mat[2][2] = cos(th);
	ft_mat_mult(mat, mat_cpy, m_rot);
}

/*
**  rot_y(th):
**  [cos(th)] [ 0 ] [-sin(th)]
**    [ 0 ]   [ 1 ]	  [ 0 ]
**  [sin(th)] [ 0 ]	[cos(th)]
*/

void		ft_y_rotation(const t_dec angle, t_mat m_rot)
{
	t_mat	mat;
	t_mat	mat_cpy;
	t_dec	th;

	if (angle == 0)
		return ;
	th = ft_deg_to_rad(angle);
	ft_set_identity(mat);
	ft_mat_copy(m_rot, mat_cpy);
	mat[0][0] = cos(th);
	mat[0][2] = -sin(th);
	mat[2][0] = sin(th);
	mat[2][2] = cos(th);
	ft_mat_mult(mat, mat_cpy, m_rot);
}

/*
**  rot_z(th):
**  [cos(th)]  [sin(th)] [ 0 ]
**  [-sin(th)] [cos(th)] [ 0 ]
**    [ 0 ]		 [ 0 ]	 [ 1 ]
*/

void		ft_z_rotation(const t_dec angle, t_mat m_rot)
{
	t_mat	mat;
	t_mat	mat_cpy;
	t_dec	th;

	if (angle == 0)
		return ;
	th = ft_deg_to_rad(angle);
	ft_set_identity(mat);
	ft_mat_copy(m_rot, mat_cpy);
	mat[0][0] = cos(th);
	mat[0][1] = sin(th);
	mat[1][0] = -sin(th);
	mat[1][1] = cos(th);
	ft_mat_mult(mat, mat_cpy, m_rot);
}
