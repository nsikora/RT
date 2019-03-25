/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_surface.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeigne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 18:28:53 by ppeigne           #+#    #+#             */
/*   Updated: 2018/08/21 14:38:20 by dtheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_sdl_load_bmp(SDL_Surface **img, const char *img_path)
{
	if (!img)
		return ;
	*img = NULL;
	*img = SDL_LoadBMP(img_path);
	if (!(*img))
	{
		ft_putstr(SDL_GetError());
		ft_putendl(". Skipping...");
	}
}

void	ft_sdl_load_img(SDL_Surface **img, const char *img_path)
{
	if (!img)
		return ;
	*img = NULL;
	*img = IMG_Load(img_path);
	if (!(*img))
	{
		ft_putendl(IMG_GetError());
		ft_putendl(". Skipping...");
	}
}

void	ft_sdl_create_surface(SDL_Surface **surf,
		const int width, const int height)
{
	*surf = SDL_CreateRGBSurface(0, width, height,
			DEPTH, RMASK, GMASK, BMASK, AMASK);
	if (!(*surf))
		ft_sdl_error("Surface could not be created! SDL_Error: ");
}

void	ft_sdl_free_surface(SDL_Surface **surf)
{
	SDL_FreeSurface(*surf);
	*surf = NULL;
}

void	ft_init_img(void)
{
	int	flags;
	int	init;

	flags = IMG_INIT_PNG;
	init = IMG_Init(flags);
	if ((init & flags) != flags)
	{
		ft_putendl("IMG_Init: Failed to init required jpg and png support!");
		ft_putendl(IMG_GetError());
	}
}
