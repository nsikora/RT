/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_transform.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeigne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 20:03:45 by ppeigne           #+#    #+#             */
/*   Updated: 2018/06/21 16:36:22 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

t_dec		ft_euclidean_norm(const t_vec vec)
{
	return (sqrt(vec[V_X] * vec[V_X]
				+ vec[V_Y] * vec[V_Y] + vec[V_Z] * vec[V_Z]));
}

void		ft_normalize(const t_vec vec, t_vec res)
{
	const t_dec	norm = ft_euclidean_norm(vec);
	t_dec		norm_inv;

	if (!norm)
		return ;
	norm_inv = 1 / norm;
	res[V_X] = vec[V_X] * norm_inv;
	res[V_Y] = vec[V_Y] * norm_inv;
	res[V_Z] = vec[V_Z] * norm_inv;
}

void		ft_mat_vec_mult(const t_mat trans, const t_vec vec, t_vec res)
{
	int		row;
	t_vec	tmp;

	row = 0;
	while (row < 3)
	{
		tmp[row] = vec[0] * trans[row][0] + vec[1] * trans[row][1]
			+ vec[2] * trans[row][2];
		row++;
	}
	ft_vec_copy(tmp, res);
}

void		ft_quat_vec_mult(const t_quat q, const t_vec v, t_vec res)
{
	t_vec	tmp;
	t_vec	cross;

	ft_cross_product(q + 1, v, tmp);
	ft_scalar_mult(tmp, 2, tmp);
	ft_cross_product(q + 1, tmp, cross);
	ft_scalar_mult(tmp, q[Q_W], tmp);
	ft_add_vec(tmp, v, res);
	ft_add_vec(res, cross, res);
}

void		ft_vec_to_quat(const t_vec vec, const t_dec angle, t_quat res)
{
	t_dec tmp;
	t_dec th;

	ft_normalize(vec, res + 1);
	th = ft_deg_to_rad(angle);
	tmp = sin(th / 2);
	res[Q_W] = cos(th / 2);
	res[Q_X] = tmp * res[Q_X];
	res[Q_Y] = tmp * res[Q_Y];
	res[Q_Z] = tmp * res[Q_Z];
}
