/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_option.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeigne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 19:25:55 by ppeigne           #+#    #+#             */
/*   Updated: 2018/08/20 19:25:57 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	ft_menu_info_option(t_env *env)
{
	(void)env;
	return ;
}

static void	ft_menu_postp_option(t_env *env)
{
	if ((env->preview_param.post == P_COLOR
			&& env->preview_param.post != P_CYAN)
				|| env->preview_param.post == P_NEG
				|| env->preview_param.post == P_GREY)
		SDL_BlitSurface(env->menu.select_option,
				NULL, env->menu.lay_base, &env->menu.option_rect[1]);
	if (env->preview_param.post == P_BLUR)
		SDL_BlitSurface(env->menu.select_option,
				NULL, env->menu.lay_base, &env->menu.option_rect[2]);
	if (env->preview_param.border == 1)
		SDL_BlitSurface(env->menu.select_option,
				NULL, env->menu.lay_base, &env->menu.option_rect[3]);
	if (env->preview_param.border == 2)
		SDL_BlitSurface(env->menu.select_option,
				NULL, env->menu.lay_base, &env->menu.option_rect[4]);
	if (env->preview_param.stereo > 0)
		SDL_BlitSurface(env->menu.select_option,
				NULL, env->menu.lay_base, &env->menu.option_rect[5]);
}

static void	ft_menu_editor_option(t_env *env)
{
	(void)env;
	return ;
}

static void	ft_menu_parameters_option(t_env *env)
{
	if (env->menu.move_or_rot)
		SDL_BlitSurface(env->menu.select_option,
			NULL, env->menu.lay_base, &env->menu.option_rect[1]);
}

void		ft_draw_option_selection(t_env *env)
{
	static void (*f_menu_option[4])(t_env*) = {&ft_menu_info_option,
											&ft_menu_postp_option,
											&ft_menu_editor_option,
											&ft_menu_parameters_option};

	(*f_menu_option[(int)env->menu.menu])(env);
}
