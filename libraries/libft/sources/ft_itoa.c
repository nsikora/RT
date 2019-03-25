/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtheo <dtheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 17:51:05 by dtheo             #+#    #+#             */
/*   Updated: 2017/11/17 20:27:39 by dtheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(int n)
{
	int		l;

	l = 0;
	if (n == 0)
		return (1);
	while (n > 0 || n < 0)
	{
		n /= 10;
		l++;
	}
	return (l);
}

char		*ft_itoa(int n)
{
	int		neg;
	int		l;
	char	*itoa;

	neg = (n < 0 ? 1 : 0);
	l = ft_intlen(n) + neg;
	if (!(itoa = ft_strnew(l)))
		return (NULL);
	if (neg)
		*itoa = '-';
	*(itoa + l--) = '\0';
	while (l >= neg)
	{
		*(itoa + l--) = ft_abs(n % 10) + '0';
		n /= 10;
	}
	return (itoa);
}
