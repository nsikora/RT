/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtheo <dtheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 15:50:04 by dtheo             #+#    #+#             */
/*   Updated: 2017/11/13 15:29:33 by dtheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!(*little))
		return ((char *)big);
	while (*(big + i) && i < n)
	{
		j = 0;
		while (*(big + i + j) == *(little + j) && (i + j) < n)
		{
			if (!(*(little + j + 1)))
				return ((char *)big + i);
			j++;
		}
		i++;
	}
	return (NULL);
}
