/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeigne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 19:48:49 by ppeigne           #+#    #+#             */
/*   Updated: 2018/06/21 16:34:51 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

void	ft_add_mat(const t_mat m1, const t_mat m2, t_mat res)
{
	ft_add_vec(m1[0], m2[0], res[0]);
	ft_add_vec(m1[1], m2[1], res[1]);
	ft_add_vec(m1[2], m2[2], res[2]);
}

void	ft_sub_mat(const t_mat m1, const t_mat m2, t_mat res)
{
	ft_sub_vec(m1[0], m2[0], res[0]);
	ft_sub_vec(m1[1], m2[1], res[1]);
	ft_sub_vec(m1[2], m2[2], res[2]);
}

void	ft_mat_mult(const t_mat m1, const t_mat m2, t_mat res)
{
	ft_mat_vec_mult(m1, m2[0], res[0]);
	ft_mat_vec_mult(m1, m2[1], res[1]);
	ft_mat_vec_mult(m1, m2[2], res[2]);
}

void	ft_set_identity(t_mat mat)
{
	mat[0][0] = 1;
	mat[0][1] = 0;
	mat[0][2] = 0;
	mat[1][0] = 0;
	mat[1][1] = 1;
	mat[1][2] = 0;
	mat[2][0] = 0;
	mat[2][1] = 0;
	mat[2][2] = 1;
}
