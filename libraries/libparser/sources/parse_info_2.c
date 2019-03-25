/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsikora <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 11:09:30 by nsikora           #+#    #+#             */
/*   Updated: 2018/08/16 17:54:00 by nsikora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void		get_info_name(char *str, int *i, t_info **info)
{
	char		*tmp;
	int			j;
	int			k;

	*i = *i + 1;
	j = *i;
	k = 0;
	while (str[*i] != ':' && str[*i] != '\0')
		*i = *i + 1;
	if (str[*i])
	{
		if ((tmp = malloc(sizeof(char) * (*i - j))) == 0)
			ft_error(MALLOC_ERROR);
		while (k < (*i - j - 1))
		{
			tmp[k] = str[j + k];
			k++;
		}
		tmp[k] = '\0';
		(*info)->str = tmp;
		(*info)->length = 0;
	}
}

static void		get_info_value_number(char *str, int *i, t_info **info)
{
	char		*cpy;
	int			cp_dot;
	int			j;

	cp_dot = 0;
	j = *i;
	if (str[*i] == '-')
		*i = *i + 1;
	while (ft_isdigit(str[*i]) == 1 || str[*i] == '.')
	{
		if (str[*i] == '.')
			cp_dot++;
		*i = *i + 1;
	}
	if ((str[*i] != ']' && str[*i] != ',' && check_useless(str[*i]) == 0)
		|| (cp_dot > 1))
		ft_error("Error: invalid float value in json array.");
	if ((cpy = malloc(sizeof(char) * (*i - j + 1))) == 0)
		ft_error(MALLOC_ERROR);
	cpy = ft_strncpy(cpy, str + j, (size_t)(*i - j));
	cpy[*i - j] = '\0';
	if (((*info)->value = malloc(sizeof(float))) == 0)
		ft_error(MALLOC_ERROR);
	*(float *)((*info)->value) = ft_fatoi(cpy);
	free(cpy);
}

static void		get_info_value_string(char *str, int *i, t_info **info)
{
	char		*tmp;
	int			can_close;
	int			j;

	*i = *i + 1;
	j = *i;
	can_close = 0;
	while (str[*i] != '"' && can_close >= 0)
	{
		if (str[*i] == '\\' && str[*i + 1] == '"')
			can_close--;
		if (str[*i] == '"')
			can_close++;
		*i = *i + 1;
	}
	if ((tmp = malloc(sizeof(char) * (*i - j) + 1)) == 0)
		ft_error(MALLOC_ERROR);
	fill_info_value_string(tmp, str, j, i);
	(*info)->value = (void *)tmp;
	(*info)->length = (int)ft_strlen(tmp);
}

void			get_info_value(char *str, int *i, t_info **info)
{
	while (check_useless(str[*i]) == 1)
		*i = *i + 1;
	if (ft_isalnum(str[*i]) == 0 && str[*i] != '-'
		&& str[*i] != '"' && str[*i] != '[')
		ft_error("Error: Invalid value format detected");
	if (ft_isalnum(str[*i]) == 1 || str[*i] == '-')
	{
		if (ft_isalpha(str[*i]) == 1)
			ft_error("Error: Invalid value format for Raytracer detected");
		if (ft_isdigit(str[*i]) == 1
			|| (str[*i] == '-' && ft_isdigit(str[*i + 1]) == 1))
			get_info_value_number(str, i, info);
	}
	if (str[*i] == '"')
		get_info_value_string(str, i, info);
	if (str[*i] == '[')
		get_info_value_array(str, i, info);
}

void			get_info(char *str, int *i, t_json_obj **obj)
{
	t_json_obj	*new;
	t_info		*info;

	new = *obj;
	if (new)
	{
		while (new->next)
			new = new->next;
		info = new->info;
		if (!info)
		{
			new->info = init_info();
			info = new->info;
		}
		else
		{
			while (info->next)
				info = info->next;
			info->next = init_info();
			info = info->next;
		}
		get_info_name(str, i, &info);
		*i = *i + 1;
		get_info_value(str, i, &info);
	}
}
