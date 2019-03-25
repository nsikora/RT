/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbard <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 19:07:52 by jbard             #+#    #+#             */
/*   Updated: 2018/08/20 19:07:53 by jbard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	ft_sdl_exit(t_env *env)
{
	ft_sdl_free_surface(&env->rt_param.lay_rt);
	ft_sdl_free_surface(&env->rt_param.lay_stereo);
	ft_sdl_free_surface(&env->rt_param.lay_border);
	ft_sdl_free_surface(&env->rt_param.lay_post);
	ft_sdl_free_surface(&env->preview_param.lay_rt);
	ft_sdl_free_surface(&env->preview_param.lay_stereo);
	ft_sdl_free_surface(&env->preview_param.lay_border);
	ft_sdl_free_surface(&env->preview_param.lay_post);
	ft_sdl_free_surface(&env->lay_menu);
	ft_sdl_free_surface(&env->menu.lay_base);
	ft_sdl_free_surface(&env->menu.lay_event);
	ft_sdl_free_surface(&env->menu.lay_logo);
	ft_sdl_free_surface(&env->menu.select_square);
	ft_sdl_free_surface(&env->menu.highlight_square);
	ft_sdl_free_surface(&env->menu.select_square);
	ft_sdl_free_surface(&env->menu.highlight_option);
	ft_sdl_free_surface(&env->menu.select_option);
	ft_sdl_destroy_win(&env->win);
	TTF_Quit();
	SDL_Quit();
	IMG_Quit();
}

void		ft_exit_properly(t_env *env)
{
	ft_sdl_exit(env);
	exit(0);
}

void		ft_malloc_error(t_env *env)
{
	ft_putendl("error: memory allocation fail");
	ft_exit_properly(env);
}

int			main(int ac, char **av)
{
	t_env	*env;

	if (ac != 2)
		ft_error("Error: Format must be ./rt filename");
	if (!(env = (t_env *)ft_memalloc(sizeof(t_env))))
		ft_malloc_error(env);
	ft_init_ocl_param(env);
	ft_ttf_init();
	ft_init_img();
	rt_info(av[1], env);
	env->menu.selected_obj = -1;
	ft_compute_menu_pos(env);
	ft_init_rt_param(env);
	ft_init_sdl(env);
	ft_load_logo_surf(env);
	ft_create_lay_logo(env);
	ft_init_all_sliders(env);
	ft_load_msg(&env->menu);
	ft_build_obj_rt(env, &env->rt_param);
	ft_build_obj_rt(env, &env->preview_param);
	ft_core(env);
	return (0);
}
