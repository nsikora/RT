/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_obj_light.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeigne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 19:26:50 by ppeigne           #+#    #+#             */
/*   Updated: 2018/08/20 19:26:52 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_edit_obj_spec(t_obj *obj, t_dec new_spec)
{
	obj->spec += new_spec;
}

void	ft_edit_obj_trans(t_obj *obj, t_dec new_trans)
{
	obj->trans += new_trans;
}

void	ft_edit_obj_refract(t_obj *obj, t_dec new_refract)
{
	obj->refract += new_refract;
}

void	ft_edit_obj_reflect(t_obj *obj, t_dec new_reflect)
{
	obj->reflect += new_reflect;
}
