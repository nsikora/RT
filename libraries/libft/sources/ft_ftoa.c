/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtheo <dtheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 00:38:05 by dtheo             #+#    #+#             */
/*   Updated: 2018/08/20 00:38:08 by dtheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_ftoa(float n, size_t precision)
{
	char		*whole;
	char		*dec;
	char		*ftoa;
	size_t		l;

	if (!(whole = ft_itoa((int)floor(n))))
		return (NULL);
	if (precision == 0)
		return (whole);
	n = fabs(n) - floor(fabs(n)) + 1;
	n = n * ft_pow(10, precision);
	if (!(dec = ft_itoa((int)floor(n))))
		return (NULL);
	l = ft_strlen(whole) + ft_strlen(dec);
	if (!(ftoa = ft_strnew(l)))
		return (NULL);
	ft_strcat(ftoa, whole);
	ftoa[ft_strlen(whole)] = '.';
	ft_strcat(ftoa + ft_strlen(whole) + 1, dec + 1);
	ft_memdel((void **)&whole);
	ft_memdel((void **)&dec);
	return (ftoa);
}
