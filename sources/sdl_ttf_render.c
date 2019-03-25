/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_ttf_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeigne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 18:29:20 by ppeigne           #+#    #+#             */
/*   Updated: 2018/08/20 18:29:21 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

SDL_Surface		*ft_ttf_render_txt_b(TTF_Font *font, const char *str,
				const SDL_Color color)
{
	SDL_Surface	*txt_surf;

	if (!(txt_surf = TTF_RenderText_Blended(font, str, color)))
		ft_ttf_error("Text failed to render! TTF_Error: ");
	return (txt_surf);
}

void			ft_ttf_render_txt_b_menu(t_env *env, const char *str,
				const SDL_Color color, SDL_Rect rect)
{
	SDL_Surface	*txt_surf;

	txt_surf = ft_ttf_render_txt_b(env->pt_mono, str, color);
	SDL_BlitSurface(txt_surf, NULL, env->menu.lay_base, &rect);
	SDL_FreeSurface(txt_surf);
}

void			ft_ttf_render_txt_b_screen(t_env *env, const char *str,
				const SDL_Color color, SDL_Rect rect)
{
	SDL_Surface	*txt_surf;

	txt_surf = ft_ttf_render_txt_b(env->pt_mono, str, color);
	SDL_BlitSurface(txt_surf, NULL, env->screen, &rect);
	SDL_FreeSurface(txt_surf);
}
