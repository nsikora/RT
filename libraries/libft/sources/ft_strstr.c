/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtheo <dtheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 15:23:17 by dtheo             #+#    #+#             */
/*   Updated: 2017/11/13 15:23:27 by dtheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	int i;
	int j;

	i = 0;
	if (!(*little))
		return ((char *)big);
	while (*(big + i))
	{
		j = 0;
		while (*(big + i + j) == *(little + j))
		{
			if (!(*(little + j + 1)))
				return ((char *)big + i);
			j++;
		}
		i++;
	}
	return (NULL);
}
