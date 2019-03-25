/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtheo <dtheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 17:48:59 by dtheo             #+#    #+#             */
/*   Updated: 2017/11/18 09:15:07 by dtheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(const char *s, char (*f)(char))
{
	char	*map;
	size_t	i;

	if (!s || !f)
		return (NULL);
	if (!(map = ft_strnew(ft_strlen(s))))
		return (NULL);
	i = 0;
	while (*s)
		*(map + i++) = (*f)(*(s++));
	return (map);
}
