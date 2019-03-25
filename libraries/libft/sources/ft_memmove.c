/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtheo <dtheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 18:20:12 by dtheo             #+#    #+#             */
/*   Updated: 2017/11/04 18:20:12 by dtheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	void	*tmp;

	if (!(tmp = ft_memalloc(sizeof(unsigned char) * n)))
		return (dest);
	i = 0;
	while (i < n)
	{
		*(unsigned char *)(tmp + i) = *(unsigned char *)(src + i);
		i++;
	}
	i = 0;
	while (i < n)
	{
		*(unsigned char *)(dest + i) = *(unsigned char *)(tmp + i);
		i++;
	}
	ft_memdel(&tmp);
	return (dest);
}
