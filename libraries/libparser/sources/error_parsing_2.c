/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_parsing_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsikora <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 13:03:16 by nsikora           #+#    #+#             */
/*   Updated: 2018/08/15 16:38:35 by nsikora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_error	*check_parse_dquote(t_parse *parse, t_error *error, char *str, int i)
{
	parse->double_quote++;
	if (parse->double_quote % 2 == 0)
	{
		while (check_useless(str[i + 1]) == 1)
			i++;
		if (str[i + 1] != '}' && str[i + 1] != ']' && str[i + 1] != ':'
			&& str[i + 1] != ',')
			error->id = ERR_DQUOTE;
	}
	if (parse->double_quote % 2 == 1)
	{
		while (i > 1 && check_useless(str[i - 1]) == 1)
			i--;
		if (i > 1 && (str[i - 1] != '{' && str[i - 1] != '[' &&
			str[i - 1] != ',' && str[i - 1] != ':'))
			error->id = ERR_DQUOTE;
	}
	return (error);
}

t_error	*check_parse_ddot(t_parse *parse, t_error *error, char *str, int i)
{
	while (check_useless(str[i + 1]) == 1)
		i++;
	if ((str[i + 1] == ',' || str[i + 1] == '}' || str[i + 1] == ']'
			|| str[i + 1] == ':') && parse->double_quote % 2 == 0)
		error->id = ERR_DDOT;
	while (str[i] != ':')
		i--;
	while (i > 1 && check_useless(str[i - 1]) == 1)
		i--;
	if (str[i - 1] != '"' && parse->double_quote % 2 == 0)
		error->id = ERR_DQUOTE;
	return (error);
}

void	error_message(t_error *error)
{
	ft_putstr("Error syntax: ");
	if (error->id == ERR_COMMA)
		ft_putstr("Invalid comma at line ");
	if (error->id == ERR_OPEN_BRACKET)
		ft_putstr("Invalid opening bracket at line ");
	if (error->id == ERR_END_BRACKET)
		ft_putstr("Invalid ending bracket at line ");
	if (error->id == ERR_NBR_BRACKET)
		ft_putstr("Invalid bracket number at line ");
	if (error->id == ERR_ARRAY)
		ft_putstr("Invalid array at line ");
	if (error->id == ERR_DQUOTE)
		ft_putstr("Invalid double quote at line ");
	if (error->id == ERR_DDOT)
		ft_putstr("Invalid double dot at line ");
	ft_putnbr(error->line);
	ft_putchar('\n');
}
