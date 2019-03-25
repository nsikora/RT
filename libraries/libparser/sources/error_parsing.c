/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsikora <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 14:58:45 by nsikora           #+#    #+#             */
/*   Updated: 2018/08/15 14:57:30 by nsikora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_error	*check_parse_comma(t_parse *parse, t_error *error, char *str, int i)
{
	if (parse->double_quote % 2 == 0)
		parse->comma++;
	if (i == 0)
		error->id = ERR_COMMA;
	while (check_useless(str[i - 1]) == 1)
		i--;
	if (i > 1 && (str[i - 1] == ',' || str[i - 1] == '[' || str[i - 1] == '{'
			|| str[i - 1] == ':') && parse->double_quote % 2 == 0)
		error->id = ERR_COMMA;
	while (str[i] != ',')
		i++;
	while (check_useless(str[i + 1]) == 1)
		i++;
	if (str[i + 1] != '"' && str[i + 1] != '[' && str[i + 1] != '{'
		&& ft_isalnum(str[i + 1] == 1) && parse->double_quote % 2 == 0)
		error->id = ERR_COMMA;
	return (error);
}

t_error	*check_parse_bracket(t_parse *parse, t_error *error, char *str, int i)
{
	if (str[i] == '{' && parse->double_quote % 2 == 0)
	{
		parse->bracket++;
		while (check_useless(str[i + 1]) == 1)
			i++;
		if (str[i + 1] != '"' && str[i + 1] != '{'
			&& ft_isalnum(str[i + 1] == 0))
			error->id = ERR_OPEN_BRACKET;
	}
	if (str[i] == '}' && parse->double_quote % 2 == 0)
	{
		parse->bracket--;
		parse->cpy = i;
		while (check_useless(str[i - 1]) == 1)
			i--;
		if (i > 1 && (str[i - 1] == ',' || str[i - 1] == '[' ||
			str[i - 1] == ':'))
			error->id = ERR_END_BRACKET;
		while (check_useless(str[parse->cpy + 1]) == 1)
			parse->cpy++;
		if (str[parse->cpy + 1] != ',' && str[parse->cpy + 1] != '}'
			&& str[parse->cpy + 1] != ']' && str[parse->cpy + 1] != '\0')
			error->id = ERR_COMMA;
	}
	return (error);
}

t_error	*check_parse_array(t_parse *parse, t_error *error, char *str, int i)
{
	if (str[i] == '[' && parse->double_quote % 2 == 0)
	{
		parse->array++;
		while (i > 1 && check_useless(str[i - 1]) == 1)
			i--;
		if (i > 1 && str[i - 1] != ':')
			error->id = ERR_ARRAY;
	}
	if (str[i] == ']' && parse->double_quote % 2 == 0)
	{
		parse->array--;
		while (check_useless(str[i + 1]) == 1)
			i++;
		if (str[i + 1] != ',' && str[i + 1] != '}')
			error->id = ERR_ARRAY;
	}
	if (parse->array < 0)
		error->id = ERR_ARRAY;
	return (error);
}

int		check_parse_synthax(t_parse *parse, t_error *error, char *str, int i)
{
	while (str[i])
	{
		if (str[i] == '\n')
			error->line++;
		if (str[i] == ':')
			check_parse_ddot(parse, error, str, i);
		if (str[i] == '"')
			check_parse_dquote(parse, error, str, i);
		if (str[i] == ',')
			check_parse_comma(parse, error, str, i);
		if (str[i] == '{' || str[i] == '}')
			check_parse_bracket(parse, error, str, i);
		if (parse->bracket < 0)
			error->id = ERR_NBR_BRACKET;
		if (str[i] == '[' || str[i] == ']')
			check_parse_array(parse, error, str, i);
		if (error->id != 0)
			return (0);
		i++;
	}
	while (check_useless(str[i]) == 1 || str[i] == '\0')
		i--;
	if (str[i] != '}')
		error->id = ERR_END_BRACKET;
	return (0);
}

void	check_parse_error(t_parse *parse, t_error *error, char *str)
{
	int	i;

	i = 0;
	while (check_useless(str[i]) == 1)
		i++;
	if (str[i] != '{')
	{
		error->id = ERR_OPEN_BRACKET;
		error_message(error);
	}
	check_parse_synthax(parse, error, str, i);
	if (parse->bracket != 0)
		error->id = ERR_NBR_BRACKET;
	if (parse->array != 0)
		error->id = ERR_ARRAY;
	if (error->id != 0)
	{
		error_message(error);
		free(str);
		free(parse);
		free(error);
		exit(0);
	}
}
