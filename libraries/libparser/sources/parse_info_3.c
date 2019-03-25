/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsikora <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 11:46:15 by nsikora           #+#    #+#             */
/*   Updated: 2018/08/16 17:36:19 by nsikora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	fill_info_array(char *str, int *i, float *tab, int elem)
{
	t_info	*tmp;
	int		j;

	j = 0;
	tmp = init_info();
	while (elem > 0)
	{
		*i = *i + 1;
		get_info_value(str, i, &tmp);
		if (tmp->length == 0)
		{
			tab[j] = *(float *)tmp->value;
			free(tmp->value);
		}
		else
			ft_error("Error: no string allowed in array for Raytracer.");
		free(tmp->str);
		elem--;
		j++;
	}
	free(tmp);
}

static void	fill_info_value_array(t_info **info, float *tab, int elem)
{
	(*info)->length = elem;
	while (elem > 0)
	{
		((*info)->value) = tab;
		elem--;
	}
}

void		fill_info_value_string(char *tmp, char *str, int j, int *i)
{
	int		k;

	k = 0;
	while (j < *i)
	{
		tmp[k] = str[j];
		j++;
		k++;
	}
	tmp[k] = '\0';
}

void		get_info_value_array(char *str, int *i, t_info **info)
{
	float	*tab;
	int		elem;
	int		j;
	int		dquote;

	elem = 1;
	j = *i;
	dquote = 0;
	while (str[j] != ']' && str[*i] != '\0')
	{
		if (str[j] == '"' && str[j - 1] != '\\')
			dquote++;
		if (str[j] == ',' && dquote % 2 == 0)
			elem++;
		j++;
		if (str[j] == ']' && dquote % 2 == 1)
			j++;
	}
	if (elem == 0)
		ft_error("Error: array is empty.");
	if ((tab = malloc(sizeof(float) * elem)) == 0)
		ft_error(MALLOC_ERROR);
	fill_info_array(str, i, tab, elem);
	fill_info_value_array(info, tab, elem);
}
