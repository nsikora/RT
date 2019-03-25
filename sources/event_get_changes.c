/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_get_changes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbard <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 18:55:25 by jbard             #+#    #+#             */
/*   Updated: 2018/08/20 18:55:34 by jbard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** ft_move:
**
** Receive a vector 'move', transform it with camera's rotation
** quaternion and add it to camera's position.
**
** Set 'change' to 1 to compute ray-tracing.
**
** Directions:
** 	- LEFT		-> {-X,  0,  0}
** 	- RIGHT		-> {+X,  0,  0}
** 	- FORWARD	-> { 0,  0, -Z}
** 	- BACKWARD	-> { 0,  0, +Z}
** 	- UP		-> { 0, +Y,  0}
** 	- DOWN		-> { 0, -Y,  0}
*/

void			ft_rot(t_env *env, t_vec move)
{
	t_quat		q_tmp;

	ft_init_quat_with_rot(move, q_tmp);
	if (env->menu.selected_obj >= 0)
	{
		ft_quat_vec_mult(q_tmp,
				env->rt.objs[env->menu.selected_obj].dir,
				env->rt.objs[env->menu.selected_obj].dir);
		ft_rebuild_objs(env);
	}
	else
		ft_quat_vec_mult(q_tmp, env->rt.cam_rot, env->rt.cam_rot);
	env->param.change = 1;
	env->rt_param.compute = 1;
	env->preview_param.compute = 1;
}

void			ft_move(t_env *env, t_vec move)
{
	t_vec		tmp;

	if (env->menu.selected_obj >= 0)
	{
		ft_add_vec(move,
				env->rt.objs[env->menu.selected_obj].pos,
				env->rt.objs[env->menu.selected_obj].pos);
		ft_rebuild_objs(env);
	}
	else
	{
		ft_quat_vec_mult(env->rt.cam_rot, move, tmp);
		ft_add_vec(tmp, env->rt.cam_pos, env->rt.cam_pos);
	}
	env->param.change = 1;
	env->rt_param.compute = 1;
	env->preview_param.compute = 1;
}

/*
** ft_event_get_changes:
**
** Get the states of keys witdh
** `SDL_GetKeyboardState()`.
**
** Repeat an event until a key is released.
*/

void			ft_event_get_changes(t_env *env)
{
	const Uint8	*state = SDL_GetKeyboardState(NULL);
	void		(*change[2])(t_env *env, t_vec move);

	change[0] = ft_move;
	change[1] = ft_rot;
	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT))
	{
		env->param.tmp_x = env->param.mouse_pos_x;
		env->param.tmp_y = env->param.mouse_pos_y;
		env->param.mouse_right_button = 1;
	}
	else
		env->param.mouse_right_button = 0;
	if (state[SDL_SCANCODE_A])
		(*change[env->menu.move_or_rot])(env, (t_vec){-env->param.step, 0, 0});
	if (state[SDL_SCANCODE_W])
		(*change[env->menu.move_or_rot])(env, (t_vec){0, 0, -env->param.step});
	if (state[SDL_SCANCODE_S])
		(*change[env->menu.move_or_rot])(env, (t_vec){0, 0, env->param.step});
	if (state[SDL_SCANCODE_D])
		(*change[env->menu.move_or_rot])(env, (t_vec){env->param.step, 0, 0});
	if (state[SDL_SCANCODE_Q])
		(*change[env->menu.move_or_rot])(env, (t_vec){0, env->param.step, 0});
	if (state[SDL_SCANCODE_E])
		(*change[env->menu.move_or_rot])(env, (t_vec){0, -env->param.step, 0});
}
