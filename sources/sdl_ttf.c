/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_ttf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeigne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 18:29:13 by ppeigne           #+#    #+#             */
/*   Updated: 2018/08/20 18:29:14 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_ttf_error(const char *error)
{
	ft_putstr(error);
	ft_putendl(TTF_GetError());
	exit(0);
}

void	ft_ttf_close_font(TTF_Font **font)
{
	TTF_CloseFont(*font);
	*font = NULL;
}

void	ft_ttf_open_font(TTF_Font **font, const char *path, const int size)
{
	*font = TTF_OpenFont(path, size);
	if (!font)
		ft_ttf_error("Font could not be opened! TTF_Error: ");
}

void	ft_ttf_init(void)
{
	if (TTF_Init() == -1)
		ft_ttf_error("TTF could not initialize! TTF_Error: ");
}
