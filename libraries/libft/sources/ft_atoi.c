/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtheo <dtheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 22:53:40 by dtheo             #+#    #+#             */
/*   Updated: 2017/11/18 08:11:17 by dtheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *nptr)
{
	long	atoi;
	int		neg;

	atoi = 0;
	while (ft_isspace(*nptr))
		nptr++;
	neg = (*nptr == '-' ? 1 : 0);
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while (ft_isdigit(*nptr))
		atoi = atoi * 10 + (*(nptr++) - '0');
	if (neg)
		atoi = -atoi;
	return ((int)atoi);
}
