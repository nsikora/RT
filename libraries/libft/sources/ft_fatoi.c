/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fatoi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtheo <dtheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 22:12:01 by dtheo             #+#    #+#             */
/*   Updated: 2018/07/19 12:56:07 by nsikora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float				ft_fatoi(const char *str)
{
	float			atoi;
	int				neg;
	int				div;

	atoi = 0.0;
	while (ft_isspace(*str))
		str++;
	neg = (*str == '-' ? 1 : 0);
	if (*str == '+' || *str == '-')
		str++;
	while (ft_isdigit(*str))
		atoi = atoi * 10 + (*(str++) - '0');
	if (*str == '.')
	{
		div = 10;
		while (ft_isdigit(*(++str)) && div <= 1000000)
		{
			atoi += (float)(*str - '0') / div;
			div *= 10;
		}
	}
	if (neg)
		atoi = -atoi;
	return (atoi);
}
