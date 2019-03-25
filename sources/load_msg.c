/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_msg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeigne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 19:11:50 by ppeigne           #+#    #+#             */
/*   Updated: 2018/08/20 19:12:16 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			ft_load_msg_add(char *str, char ***msg, size_t n)
{
	char			**new_msg;
	size_t			i;

	if (!(new_msg = (char **)ft_memalloc(sizeof(char *) * n)))
		return ;
	i = 0;
	while (i < n - 1 && *msg != NULL)
	{
		new_msg[i] = (*msg)[i];
		i++;
	}
	new_msg[i] = str;
	if (*msg)
		free(*msg);
	*msg = new_msg;
}

void				ft_load_msg(t_menu *menu)
{
	char			**msg;
	char			*buffer;
	int				fd;
	size_t			nb;

	msg = NULL;
	nb = 0;
	if ((fd = open(LOAD_FILE, O_RDONLY)) < 0)
	{
		menu->loading_msg = NULL;
		return ;
	}
	while (get_next_line(fd, &buffer) > 0)
	{
		ft_load_msg_add(buffer, &msg, ++nb);
		if (!msg)
			return ;
	}
	menu->loading_msg = msg;
	menu->loading_msg_size = nb;
}
