/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtheo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 15:40:14 by dtheo             #+#    #+#             */
/*   Updated: 2017/12/21 05:29:51 by dtheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	gnl_read(const int fd, char **save)
{
	char			*buffer;
	char			*tmp;
	int				bytes;

	if (!(buffer = ft_strnew(BUFF_SIZE)))
		return (-1);
	if ((bytes = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		if (!(tmp = ft_strjoin(*save, buffer)))
			return (-1);
		ft_strdel(save);
		*save = tmp;
		ft_strclr(buffer);
	}
	ft_strdel(&buffer);
	return (bytes);
}

static char	*gnl_first_line(char **save, char *newline)
{
	char			*line;

	if (!newline)
	{
		if (!(line = ft_strdup(*save)))
			return (NULL);
		ft_strdel(save);
	}
	else
	{
		if (!(line = ft_strsub(*save, 0, newline - *save)))
			return (NULL);
		newline = ft_strdup(newline + 1);
		ft_strdel(save);
		*save = newline;
	}
	return (line);
}

int			get_next_line(const int fd, char **line)
{
	static char		*save = NULL;
	char			*newline;
	int				ret;

	if (fd < 0 || !line || (!save && !(save = ft_strnew(0))))
		return (-1);
	newline = ft_strchr(save, '\n');
	while (!newline)
	{
		ret = gnl_read(fd, &save);
		if (ret == 0)
		{
			if (ft_strlen(save) == 0)
				return (0);
			break ;
		}
		else if (ret < 0)
			return (-1);
		else
			newline = ft_strchr(save, '\n');
	}
	if (!(*line = gnl_first_line(&save, newline)))
		return (-1);
	return (1);
}
