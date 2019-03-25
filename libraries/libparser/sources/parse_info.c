/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsikora <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 10:57:19 by nsikora           #+#    #+#             */
/*   Updated: 2018/08/21 15:00:38 by nsikora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static t_json_obj	*init_object(void)
{
	t_json_obj		*obj;

	if ((obj = malloc(sizeof(t_json_obj))) == 0)
		ft_error(MALLOC_ERROR);
	obj->str = NULL;
	obj->info = NULL;
	obj->next = NULL;
	return (obj);
}

t_info				*init_info(void)
{
	t_info		*info;

	if ((info = malloc(sizeof(t_info))) == 0)
		ft_error(MALLOC_ERROR);
	info->length = 0;
	info->str = NULL;
	info->value = NULL;
	info->next = NULL;
	return (info);
}

static void			skip_useless(char *str, int *i)
{
	int				dquote;

	dquote = 0;
	while (str[*i] != '{' && str[*i] != ',' && str[*i] != '\0')
	{
		*i = *i + 1;
		if (str[*i] == '"')
			dquote++;
		if (dquote % 2 == 1 && str[*i] == '{' && str[*i] == '\0')
			*i = *i + 1;
	}
}

static void			get_object(char *str, int *i, int j, t_json_obj **obj)
{
	t_json_obj		*new;

	if (!(*obj))
	{
		*obj = init_object();
		new = *obj;
	}
	else
	{
		new = *obj;
		while (new->next != NULL)
			new = new->next;
		new->next = init_object();
		new = new->next;
	}
	while (str[*i] != '"' && str[*i] != '\0')
		*i = *i + 1;
	if ((new->str = malloc(sizeof(char) * (*i - j + 1))) == 0)
		ft_error(MALLOC_ERROR);
	ft_strncpy(new->str, str + j, ft_strchr(str + j, '"') - (str + j));
	new->str[*i - j] = '\0';
	skip_useless(str, i);
}

void				store_info(char *str, t_json_obj **obj, int cp)
{
	int				i;
	int				bracket;

	i = 0;
	bracket = 0;
	while (str[i] != '\0')
	{
		if (bracket == 1 && str[i] == '"')
		{
			i = i + 1;
			cp++;
			get_object(str, &i, i, obj);
		}
		if (bracket == 2 && str[i] == '"')
			get_info(str, &i, obj);
		if (str[i] == '{')
			bracket++;
		if (str[i] == '}')
		{
			bracket--;
			if (cp > 300)
				return ;
		}
		i++;
	}
}
