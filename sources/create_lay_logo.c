/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lay_logo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtheo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 14:37:49 by dtheo             #+#    #+#             */
/*   Updated: 2018/08/21 14:37:51 by dtheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_free_logo_surf(t_env *env)
{
	ft_sdl_free_surface(&env->menu.lay_logo_info);
	ft_sdl_free_surface(&env->menu.lay_logo_post);
	ft_sdl_free_surface(&env->menu.lay_logo_edit);
	ft_sdl_free_surface(&env->menu.lay_logo_para);
	ft_sdl_free_surface(&env->menu.lay_logo_shot);
	ft_sdl_free_surface(&env->menu.lay_logo_canc);
	ft_sdl_free_surface(&env->menu.lay_logo_appl);
}

void	ft_load_logo_surf(t_env *env)
{
	ft_sdl_load_img(&env->menu.lay_logo_info, LOGO_INFO);
	ft_sdl_load_img(&env->menu.lay_logo_post, LOGO_POST);
	ft_sdl_load_img(&env->menu.lay_logo_edit, LOGO_EDIT);
	ft_sdl_load_img(&env->menu.lay_logo_para, LOGO_PARA);
	ft_sdl_load_img(&env->menu.lay_logo_shot, LOGO_SHOT);
	ft_sdl_load_img(&env->menu.lay_logo_canc, LOGO_CANC);
	ft_sdl_load_img(&env->menu.lay_logo_appl, LOGO_APPL);
}

void	ft_create_lay_logo(t_env *env)
{
	SDL_BlitScaled(env->menu.lay_logo_info, NULL,
		env->menu.lay_logo, &env->menu.logo_coor[0]);
	SDL_BlitScaled(env->menu.lay_logo_post, NULL,
		env->menu.lay_logo, &env->menu.logo_coor[1]);
	SDL_BlitScaled(env->menu.lay_logo_edit, NULL,
		env->menu.lay_logo, &env->menu.logo_coor[2]);
	SDL_BlitScaled(env->menu.lay_logo_para, NULL,
		env->menu.lay_logo, &env->menu.logo_coor[3]);
	SDL_BlitScaled(env->menu.lay_logo_shot, NULL,
		env->menu.lay_logo, &env->menu.logo_coor[4]);
	SDL_BlitScaled(env->menu.lay_logo_canc, NULL,
		env->menu.lay_logo, &env->menu.logo_coor[5]);
	SDL_BlitScaled(env->menu.lay_logo_appl, NULL,
		env->menu.lay_logo, &env->menu.logo_coor[6]);
}
