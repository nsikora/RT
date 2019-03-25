/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtheo <dtheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 00:02:45 by dtheo             #+#    #+#             */
/*   Updated: 2018/06/25 14:33:17 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_len(const char *s, char c)
{
	size_t	r;

	r = 0;
	while (*s)
	{
		if (*s != c)
		{
			while (*s != c && *s)
				s++;
			r++;
		}
		else
			s++;
	}
	return (r);
}

static size_t	ft_wordlen(const char *s, char c)
{
	size_t	r;

	r = 0;
	while (*(s + r) && *(s + r) != c)
		r++;
	return (r);
}

char			**ft_strsplit(const char *s, char c)
{
	char	**split;
	char	*word;
	size_t	i;

	if (!s || !(split = (char **)malloc(sizeof(char *) * (ft_len(s, c) + 1))))
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			if (!(word = ft_strnew(ft_wordlen(s, c) + 1)))
				return (NULL);
			*(split + i) = word;
			while (*s && *s != c)
				*(word++) = *(s++);
			*word = '\0';
			i++;
		}
		else
			s++;
	}
	*(split + i) = NULL;
	return (split);
}
