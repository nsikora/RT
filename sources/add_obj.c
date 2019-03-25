/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtheo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 08:36:02 by dtheo             #+#    #+#             */
/*   Updated: 2018/08/21 08:36:04 by dtheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_obj			ft_new_obj(void)
{
	t_obj		obj;

	obj.type = ID_SPHERE;
	obj.pos[V_X] = 0;
	obj.pos[V_Y] = 0;
	obj.pos[V_Z] = 0;
	obj.dir[V_X] = 0;
	obj.dir[V_Y] = 1;
	obj.dir[V_Z] = 0;
	obj.scl[0] = 1;
	obj.scl[1] = 1;
	obj.scl[2] = 1;
	obj.spec = 1;
	obj.trans = 0;
	obj.refract = 1;
	obj.texture = -1;
	obj.texture_scl = 1;
	obj.texture_norm = -1;
	obj.texture_mode = 0;
	obj.texture_spec = -1;
	obj.texture_xoff = 0;
	obj.texture_yoff = 0;
	obj.reflect = 0;
	obj.color.rgb = 0xFFFFFFFF;
	return (obj);
}

void			ft_copy_objs(t_obj *dest, t_obj *src, size_t len)
{
	size_t		i;

	i = 0;
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
}

void			ft_add_obj(t_env *env)
{
	t_obj		*objs;
	size_t		len;

	len = env->rt_param.mem_objs.nb_obj + 1;
	if (!(objs = (t_obj *)ft_memalloc(sizeof(t_obj) * len)))
		return ;
	env->rt.objs[len - 2] = ft_new_obj();
	ft_memcpy(objs, env->rt.objs, (len - 1) * sizeof(t_obj));
	objs[len - 1].type = -1;
	free(env->rt.objs);
	env->rt.objs = objs;
	env->rt_param.mem_objs.nb_obj = len;
	env->preview_param.mem_objs.nb_obj = len;
	ft_rebuild_objs(env);
	env->rt_param.compute = 1;
	env->preview_param.compute = 1;
	env->param.change = 1;
}
