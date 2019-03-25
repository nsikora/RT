/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_load.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeigne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 18:04:54 by ppeigne           #+#    #+#             */
/*   Updated: 2018/08/20 18:07:53 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		ft_tex_pixels_3(t_tex *tex)
{
	unsigned char	*p;
	int				k;
	int				i;

	p = (unsigned char *)(tex->surface->pixels);
	if (!(tex->pixels = (t_color *)ft_memalloc(sizeof(t_color)
			* tex->width * tex->height)))
		return ;
	i = -1;
	while (++i < tex->height * tex->width)
	{
		k = -1;
		while (++k < 3)
			tex->pixels[i].byte[k] = p[i * 3 + (2 - k)];
		tex->pixels[i].byte[k] = 255;
	}
}

static void		ft_tex_pixels_2(t_tex *tex)
{
	Uint16			*p;
	int				k;
	int				i;

	p = (Uint16 *)(tex->surface->pixels);
	if (!(tex->pixels = (t_color *)ft_memalloc(sizeof(t_color)
			* tex->width * tex->height)))
		return ;
	i = -1;
	while (++i < tex->height * tex->width)
	{
		k = -1;
		while (++k < 3)
			tex->pixels[i].byte[k] = p[i] / 0x0100;
		tex->pixels[i].byte[k] = p[i] % 0x0100;
	}
}

static void		ft_tex_pixels_1(t_tex *tex)
{
	Uint8				*p;
	SDL_Color			c;
	int					i;

	p = (Uint8 *)(tex->surface->pixels);
	if (!(tex->pixels = (t_color *)ft_memalloc(sizeof(t_color)
			* tex->width * tex->height)))
		return ;
	i = -1;
	while (++i < tex->height * tex->width)
	{
		c = tex->surface->format->palette->colors[p[i]];
		tex->pixels[i].byte[0] = c.r;
		tex->pixels[i].byte[1] = c.g;
		tex->pixels[i].byte[2] = c.b;
		tex->pixels[i].byte[3] = c.a;
	}
}

static void		ft_tex_pixels(t_tex *tex)
{
	int				bpp;

	bpp = tex->surface->format->BytesPerPixel;
	if (bpp == 4)
		ft_tex_pixels_4(tex);
	else if (bpp == 3)
		ft_tex_pixels_3(tex);
	else if (bpp == 2)
		ft_tex_pixels_2(tex);
	else if (bpp == 1)
		ft_tex_pixels_1(tex);
	else
		tex->pixels = NULL;
}

t_tex			ft_texture_load(const char *file)
{
	t_tex		tex;

	ft_sdl_load_bmp(&tex.surface, file);
	if (tex.surface != NULL)
	{
		tex.width = tex.surface->w;
		tex.height = tex.surface->h;
		tex.name = ft_strdup(ft_strrchr(file, '/') + 1);
		ft_tex_pixels(&tex);
	}
	else
		tex.pixels = NULL;
	return (tex);
}
