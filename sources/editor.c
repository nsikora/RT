/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeigne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 19:12:30 by ppeigne           #+#    #+#             */
/*   Updated: 2018/08/20 19:12:46 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	ft_selector_sliders(t_env *env)
{
	env->menu.color[0].val =
		env->rt.objs[env->menu.selected_obj].color.byte[0];
	env->menu.color[1].val =
		env->rt.objs[env->menu.selected_obj].color.byte[1];
	env->menu.color[2].val =
		env->rt.objs[env->menu.selected_obj].color.byte[2];
	env->menu.trans.val = env->rt.objs[env->menu.selected_obj].trans;
	env->menu.reflection.val = env->rt.objs[env->menu.selected_obj].reflect;
	env->menu.refraction.val = env->rt.objs[env->menu.selected_obj].refract;
	env->menu.spec.val = env->rt.objs[env->menu.selected_obj].spec;
	env->menu.tex_scl.val = env->rt.objs[env->menu.selected_obj].texture_scl;
	if (env->menu.tex_switch == 0)
		env->menu.tex.val = env->rt.objs[(int)env->menu.selected_obj].texture;
	else if (env->menu.tex_switch == 1)
		env->menu.tex.val =
			env->rt.objs[(int)env->menu.selected_obj].texture_norm;
	else if (env->menu.tex_switch == 2)
		env->menu.tex.val =
			env->rt.objs[(int)env->menu.selected_obj].texture_spec;
	ft_selector_sliders2(env);
}

static void	ft_select_obj(int id, t_env *env)
{
	if (env->menu.selected_obj >= 0)
	{
		env->rt.objs[env->menu.selected_obj].color = env->menu.last_color;
		env->rt.objs[env->menu.selected_obj].texture = env->menu.last_tex;
		if (id == env->menu.selected_obj)
			id = -1;
	}
	env->menu.selected_obj = id;
	if (id >= 0)
	{
		ft_selector_sliders(env);
		env->menu.last_color = env->rt.objs[id].color;
		env->menu.last_tex = env->rt.objs[id].texture;
		env->menu.tex_mode_switch = env->rt.objs[id].texture_mode;
		env->menu.type_switch = env->rt.objs[env->menu.selected_obj].type;
		env->rt.objs[id].color.rgb = SOLARIZED_ACCENT_YELLOW;
		env->rt.objs[id].texture = -1;
	}
	ft_rebuild_objs(env);
	env->param.change = 1;
	env->rt_param.compute = 1;
	env->preview_param.compute = 1;
}

void		ft_selector(t_env *env)
{
	int		id;
	size_t	size;
	cl_mem	mem_id;

	size = 1;
	mem_id = clCreateBuffer(env->ocl_rt.context,
		CL_MEM_WRITE_ONLY, sizeof(int), NULL, NULL);
	ft_set_arg_selector(env, &env->rt_param, &mem_id);
	clEnqueueNDRangeKernel(*env->ocl_rt.queue,
		env->ocl_rt.kernel[K_SELECTOR_ID], 1, NULL, &size, NULL, 0, NULL, NULL);
	clFinish(*env->ocl_rt.queue);
	clEnqueueReadBuffer(*env->ocl_rt.queue, mem_id,
			CL_TRUE, 0, sizeof(int), &id, 0, NULL, NULL);
	clFinish(*env->ocl_rt.queue);
	clReleaseMemObject(mem_id);
	ft_select_obj(id, env);
}

static void	ft_draw_basis(t_vec axis, int c, SDL_Surface *s)
{
	size_t	coor[4];
	int		sq_size;

	coor[0] = s->w - 70;
	coor[1] = 70;
	coor[2] = coor[0] + floor(axis[V_X] * 40);
	coor[3] = coor[1] + floor(axis[V_Y] * 40);
	ft_bresenham(coor, (int *)(s->pixels), s->w, c);
	sq_size = 5 - (axis[V_Z] + 1) / 2 * 4;
	coor[0] = coor[2] - sq_size;
	coor[1] = coor[3] - sq_size;
	coor[2] = coor[2] + sq_size;
	coor[3] = coor[3] + sq_size;
	ft_draw_square(coor, (int *)(s->pixels), s->w, c);
}

void		ft_draw_ortho(t_env *env)
{
	t_vec					axis;
	int						c[3];
	int						i;

	c[0] = SOLARIZED_ACCENT_RED_R;
	c[1] = ORTHONORMAL_GREEN;
	c[2] = SOLARIZED_ACCENT_BLUE_R;
	i = -1;
	while (++i < 3)
	{
		axis[0] = 0;
		axis[1] = 0;
		axis[2] = 0;
		axis[i] = -1;
		ft_quat_vec_mult(env->rt.cam_rot, axis, axis);
		if (i == 1)
			axis[2] *= -1;
		ft_draw_basis(axis, c[i], env->screen);
	}
}
