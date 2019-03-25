/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtheo <dtheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 04:24:00 by dtheo             #+#    #+#             */
/*   Updated: 2017/11/13 16:09:06 by dtheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	len_src;
	size_t	len_dest;

	len_src = ft_strlen(src);
	len_dest = ft_strlen(dest);
	if (len_dest >= n)
		return (n + len_src);
	if (len_src + len_dest < n)
		ft_strncpy(dest + len_dest, src, len_src + 1);
	else
	{
		ft_strncpy(dest + len_dest, src, n - len_dest - 1);
		*(dest + n - 1) = '\0';
	}
	return (len_src + len_dest);
}
