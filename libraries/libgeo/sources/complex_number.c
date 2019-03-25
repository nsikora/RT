/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_number.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeigne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 13:25:41 by ppeigne           #+#    #+#             */
/*   Updated: 2018/06/22 13:25:46 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

void		ft_add_cpx(const t_cpx c1, const t_cpx c2, t_cpx res)
{
	res[C_R] = c1[C_R] + c2[C_R];
	res[C_I] = c1[C_I] + c2[C_I];
}

void		ft_sub_cpx(const t_cpx c1, const t_cpx c2, t_cpx res)
{
	res[C_R] = c1[C_R] - c2[C_R];
	res[C_I] = c1[C_I] - c2[C_I];
}

void		ft_cpx_mult(const t_cpx c1, const t_cpx c2, t_cpx result)
{
	t_cpx	tmp;

	tmp[C_R] = c1[C_R];
	tmp[C_I] = c1[C_I];
	result[C_R] = tmp[C_R] * c2[C_R] - tmp[C_I] * c2[C_I];
	result[C_I] = tmp[C_R] * c2[C_I] + tmp[C_I] * c2[C_R];
}

void		ft_cpx_to_power(const t_cpx cpx, int power, t_cpx result)
{
	ft_cpx_mult(cpx, cpx, result);
	power--;
	while (power > 1)
	{
		ft_cpx_mult(result, cpx, result);
		power--;
	}
}
