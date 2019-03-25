/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slider_fov.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeigne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 18:10:18 by ppeigne           #+#    #+#             */
/*   Updated: 2018/08/20 18:14:53 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			ft_init_slider_fov(t_menu *menu)
{
	ft_update_slider(menu, &menu->fov, menu->fov_rect, 6);
	menu->fov.empty.rgb = (int)0xFFFAFAFA;
	menu->fov.fill = (t_color)SOLARIZED_ACCENT_CYAN;
	menu->fov.min = 1;
	menu->fov.max = 179;
	menu->fov.val = DEFAULT_FOV;
}

int				ft_event_slider_fov(t_env *env)
{
	if (ft_event_slider(env, &env->menu.fov, env->param.mouse_pos_x,
			env->param.mouse_pos_y))
	{
		env->preview_param.fov = env->menu.fov.val;
		env->preview_param.scale = tan(ft_deg_to_rad(env->preview_param.fov
					* 0.5));
		if (env->menu.fov_val)
			free(env->menu.fov_val);
		env->menu.fov_val = ft_itoa(env->preview_param.fov);
		env->preview_param.compute = 1;
		env->param.change = 1;
		return (1);
	}
	return (0);
}

void			ft_compute_str_fov(t_env *env)
{
	int			width;
	int			height;

	TTF_SizeText(env->pt_mono, "FOV  ", &width, &height);
	if (env->menu.fov_val)
		free(env->menu.fov_val);
	env->menu.fov_val = ft_itoa(env->preview_param.fov);
	env->menu.fov_rect = (SDL_Rect){env->menu.sub_menu_coor[0] + width,
		env->menu.str_rect[6].y - env->menu.button_coor[0].h / 3, 0, height};
}

void			ft_draw_slider_fov(t_env *env)
{
	SDL_Rect	rect;

	rect = env->menu.str_rect[6];
	rect.y -= env->menu.button_coor[0].h / 3;
	ft_ttf_render_txt_b_menu(env, "FOV", env->menu.orange, rect);
	ft_ttf_render_txt_b_menu(env, env->menu.fov_val,
	env->menu.white, env->menu.fov_rect);
	ft_draw_slider(&env->menu, &env->menu.fov);
}
