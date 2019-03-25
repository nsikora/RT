/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_load2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeigne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 18:04:54 by ppeigne           #+#    #+#             */
/*   Updated: 2018/08/20 18:07:36 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ft_tex_pixels_4(t_tex *tex)
{
	t_color			*p;
	unsigned char	tmp;
	int				i;

	p = (t_color *)(tex->surface->pixels);
	if (!(tex->pixels = (t_color *)ft_memalloc(sizeof(t_color)
			* tex->width * tex->height)))
		return ;
	i = -1;
	while (++i < tex->height * tex->width)
	{
		tex->pixels[i] = p[i];
		tmp = tex->pixels[i].byte[0];
		tex->pixels[i].byte[0] = tex->pixels[i].byte[2];
		tex->pixels[i].byte[2] = tmp;
	}
}
