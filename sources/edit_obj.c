/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeigne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 19:25:25 by ppeigne           #+#    #+#             */
/*   Updated: 2018/08/20 19:26:43 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_edit_obj_pos(t_obj *obj, t_vec_ocl new_pos)
{
	obj->pos[0] += new_pos[0];
	obj->pos[1] += new_pos[1];
	obj->pos[2] += new_pos[2];
}

void	ft_edit_obj_scl(t_obj *obj, t_vec_ocl new_scl)
{
	obj->scl[0] += new_scl[0];
	obj->scl[1] += new_scl[1];
	obj->scl[2] += new_scl[2];
}

void	ft_edit_obj_dir(t_obj *obj, t_vec_ocl new_dir)
{
	obj->dir[0] += new_dir[0];
	obj->dir[1] += new_dir[1];
	obj->dir[2] += new_dir[2];
}

void	ft_edit_obj_type(t_obj *obj, int new_type)
{
	obj->type += new_type;
}
