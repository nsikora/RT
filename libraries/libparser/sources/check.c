/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_ext.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsikora <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 12:25:02 by nsikora           #+#    #+#             */
/*   Updated: 2018/08/16 17:53:30 by nsikora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int		check_useless(char c)
{
	if (c == '\t' || c == '\n' || c == ' ')
		return (1);
	return (0);
}

int		check_ext(char *file)
{
	int	i;

	i = 0;
	while (file[i] != '\0')
		i++;
	while (file[i] != '.' && i > 0)
		i--;
	if ((ft_strcmp(".json", file + i)) != 0 || file[i] == '\0')
		ft_error("Error: invalid file extension. Must be a .json");
	return (0);
}
