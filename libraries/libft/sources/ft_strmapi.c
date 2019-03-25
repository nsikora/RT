/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtheo <dtheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 18:09:49 by dtheo             #+#    #+#             */
/*   Updated: 2017/11/18 09:15:29 by dtheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char	*map;
	size_t	i;

	if (!s || !f)
		return (NULL);
	if (!(map = ft_strnew(ft_strlen(s))))
		return (NULL);
	i = 0;
	while (*(s + i))
	{
		*(map + i) = (*f)(i, *(s + i));
		i++;
	}
	return (map);
}
