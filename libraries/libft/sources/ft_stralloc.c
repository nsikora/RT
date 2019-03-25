/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stralloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtheo <dtheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 14:18:29 by dtheo             #+#    #+#             */
/*   Updated: 2017/11/22 14:19:53 by dtheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_stralloc(const char *s)
{
	char	*str;

	if (!(str = ft_strnew(ft_strlen(s))))
		return (NULL);
	return (str);
}
