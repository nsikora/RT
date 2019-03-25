/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_create_surf.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbard <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 19:06:53 by jbard             #+#    #+#             */
/*   Updated: 2018/08/20 19:06:54 by jbard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_menu_create_surf(SDL_Surface **surf, int width, int height,
		int color)
{
	ft_sdl_create_surface(surf, width, height);
	SDL_FillRect(*surf, NULL, color);
}
