/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elem_nb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsikora <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/30 14:17:54 by nsikora           #+#    #+#             */
/*   Updated: 2018/08/17 11:35:50 by nsikora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int			get_obj_nb(t_json_obj *obj)
{
	int		i;

	i = 0;
	while (obj)
	{
		if (ft_strcmp(obj->str, "sphere") == 0
			|| ft_strcmp(obj->str, "cylinder") == 0
			|| ft_strcmp(obj->str, "cone") == 0
			|| ft_strcmp(obj->str, "plane") == 0
			|| ft_strcmp(obj->str, "cube") == 0)
			i++;
		else if (ft_strcmp(obj->str, "ui") != 0
			&& ft_strcmp(obj->str, "texture") != 0
			&& ft_strcmp(obj->str, "filter") != 0
			&& ft_strcmp(obj->str, "light") != 0
			&& ft_strcmp(obj->str, "camera") != 0)
		{
			ft_putstr("Warning: This object will be ignored: \"");
			ft_putstr(obj->str);
			ft_putendl("\" is not a valid object for Raytracer.");
		}
		obj = obj->next;
	}
	return (i);
}

int			get_light_nb(t_json_obj *obj)
{
	int		i;

	i = 0;
	while (obj)
	{
		if (ft_strcmp(obj->str, "light") == 0)
			i++;
		obj = obj->next;
	}
	return (i);
}

int			get_texture_nb(t_json_obj *obj)
{
	t_info	*tmp;
	int		i;

	i = 0;
	while (obj)
	{
		if (ft_strcmp(obj->str, "texture") == 0)
		{
			tmp = obj->info;
			while (tmp)
			{
				if (ft_strcmp(tmp->str, "path") == 0)
					i++;
				tmp = tmp->next;
			}
		}
		obj = obj->next;
	}
	return (i);
}
