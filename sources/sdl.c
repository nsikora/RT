/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeigne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 18:28:41 by ppeigne           #+#    #+#             */
/*   Updated: 2018/08/20 18:28:42 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_sdl_error(const char *error)
{
	ft_putstr(error);
	ft_putendl(SDL_GetError());
	exit(0);
}

void	ft_sdl_destroy_win(SDL_Window **win)
{
	SDL_DestroyWindow(*win);
	*win = NULL;
}

void	ft_sdl_init(t_env *env, const int width, const int height)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		ft_sdl_error("SDL could not initialize! SDL_Error: ");
	env->win = SDL_CreateWindow("RT",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			env->param.width, env->param.height,
			SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (!env->win)
		ft_sdl_error("Window could not be created! SDL_Error: ");
	SDL_SetWindowMinimumSize(env->win, width, height);
	env->screen = SDL_GetWindowSurface(env->win);
}
