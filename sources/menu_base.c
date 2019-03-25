/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbard <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 19:06:42 by jbard             #+#    #+#             */
/*   Updated: 2018/08/20 19:06:43 by jbard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	ft_draw_selection(t_env *env)
{
	SDL_Rect rect;

	rect = (SDL_Rect){env->menu.button_coor[(int)env->menu.menu].x,
		env->menu.button_coor[(int)env->menu.menu].y, 0, 0};
	SDL_BlitSurface(env->menu.select_square, NULL, env->menu.lay_base, &rect);
}

static void	ft_draw_all_borders(t_env *env)
{
	ft_draw_square((size_t[4]){env->menu.rt_rect.x, 0, env->param.width,
		5}, env->menu.lay_base->pixels, env->param.width, MENU_DARK_BLUE);
	ft_draw_square((size_t[4]){0, env->menu.menu_coor[3], 5, env->param.height},
		env->menu.lay_base->pixels, env->param.width, MENU_DARK_BLUE);
	ft_draw_square((size_t[4]){0, env->param.height - 5, env->param.width,
		env->param.height}, env->menu.lay_base->pixels, env->param.width,
		MENU_DARK_BLUE);
	ft_draw_square((size_t[4]){env->param.width - 5, 0, env->param.width,
		env->param.height}, env->menu.lay_base->pixels, env->param.width,
		MENU_DARK_BLUE);
	ft_draw_square((size_t[4]){env->menu.menu_coor[0],
		env->menu.menu_coor[3] - 5, env->menu.menu_coor[2],
		env->menu.menu_coor[3]}, env->menu.lay_base->pixels, env->param.width,
		MENU_DARK_BLUE);
}

void		ft_draw_menu(t_env *env)
{
	SDL_Rect rect;

	SDL_FillRect(env->menu.lay_base, NULL, 0);
	ft_draw_all_gradients(env);
	rect = (SDL_Rect){env->menu.menu_coor[0], env->menu.menu_coor[1], 0, 0};
	SDL_BlitSurface(env->menu.menu_square, NULL, env->menu.lay_base, &rect);
	ft_draw_selection(env);
	ft_draw_option_selection(env);
	ft_draw_all_borders(env);
	ft_draw_all_angles(env);
	ft_draw_menu_str(env);
	env->menu.redraw = 0;
}
