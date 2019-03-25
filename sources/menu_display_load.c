/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_display_load.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeigne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 19:25:45 by ppeigne           #+#    #+#             */
/*   Updated: 2018/08/20 19:25:47 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ft_display_load(t_env *env)
{
	static size_t			i = 0;
	int						width;
	int						height;
	char					*str;

	str = env->menu.loading_msg[i++];
	if (i >= env->menu.loading_msg_size)
		i = 0;
	ft_ttf_render_txt_b_screen(env, STR_LOAD, env->menu.white,
	(SDL_Rect){env->menu.loading_pos[0], env->menu.loading_pos[1], 0, 0});
	TTF_SizeText(env->pt_mono, str, &width, &height);
	width = env->menu.rt_rect.x + env->menu.rt_rect.w / 2 - width / 2;
	ft_ttf_render_txt_b_screen(env, str, env->menu.orange,
	(SDL_Rect){width, env->menu.loading_pos[1] + height + 20, 0, 0});
	SDL_UpdateWindowSurface(env->win);
}
