/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtheo <dtheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 15:48:04 by dtheo             #+#    #+#             */
/*   Updated: 2017/11/18 09:18:58 by dtheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strtrim_end(char *s)
{
	int		i;

	i = 0;
	while (*s && *(s + i + 1))
		i++;
	while (*(s + i) && ft_isspace(*(s + i)))
		i--;
	return (s + i);
}

static char	*ft_strtrim_start(char *s)
{
	while (ft_isspace(*s))
		s++;
	return (s);
}

char		*ft_strtrim(const char *s)
{
	char	*end;
	char	*start;
	char	*trim;
	size_t	i;

	if (!s)
		return (NULL);
	start = ft_strtrim_start((char *)s);
	end = ft_strtrim_end(start) + 1;
	if (!(trim = ft_strnew(end - start)))
		return (NULL);
	i = 0;
	while (start < end)
		*(trim + i++) = *(start++);
	return (trim);
}
