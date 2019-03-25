/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slider_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtheo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 15:28:28 by dtheo             #+#    #+#             */
/*   Updated: 2018/08/21 15:28:29 by dtheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			ft_init_slider_tex(t_env *env, t_menu *menu)
{
	ft_update_slider(menu, &menu->tex, menu->tex_rect, 3);
	menu->tex.empty.rgb = (int)0xFFFAFAFA;
	menu->tex.fill.rgb = (int)SOLARIZED_ACCENT_ORANGE;
	menu->tex.min = -3;
	menu->tex.max = env->rt_param.mem_objs.nb_tex - 0.1;
	menu->tex.val = -1;
}

int				ft_event_slider_tex(t_env *env)
{
	if (ft_event_slider(env, &env->menu.tex, env->param.mouse_pos_x,
			env->param.mouse_pos_y))
	{
		if (env->menu.selected_obj >= 0)
			ft_event_slider_tex2(env);
		if (env->menu.tex_val)
			free(env->menu.tex_val);
		env->menu.tex_val = ft_name_slider_tex(env);
		return (1);
	}
	return (0);
}

char			*ft_name_slider_tex(t_env *env)
{
	char		*str;

	if (env->menu.tex.min == 0)
		ft_init_slider_tex(env, &env->menu);
	if (floor(env->menu.tex.val) == -1)
		return (ft_strdup("No tex"));
	else if (floor(env->menu.tex.val) == -2)
	{
		if (env->menu.tex_switch == 1)
			return (ft_strdup("Sinus"));
		return (ft_strdup("Chessboard"));
	}
	else if (floor(env->menu.tex.val) == -3)
		return (ft_strdup("Perlin"));
	else if (!(env->rt.textures[(int)env->menu.tex.val].pixels))
		return (ft_strdup("Tex Error"));
	if (!(str = ft_strnew(11)))
		return (NULL);
	ft_strncat(str, env->rt.textures[(int)env->menu.tex.val].name, 11);
	return (str);
}

void			ft_compute_str_tex(t_env *env)
{
	int			width;
	int			height;

	TTF_SizeText(env->pt_mono, "TEX", &width, &height);
	if (env->menu.tex_val)
		free(env->menu.tex_val);
	env->menu.tex_val = ft_name_slider_tex(env);
	env->menu.tex_rect = (SDL_Rect){env->menu.sub_menu_coor[0] + 5,
		env->menu.str_rect[3].y - env->menu.button_coor[0].h / 3, 0, height};
}

void			ft_draw_slider_tex(t_env *env)
{
	SDL_Rect	rect;

	rect = env->menu.str_rect[3];
	rect.y -= env->menu.button_coor[0].h / 3;
	ft_ttf_render_txt_b_menu(env, env->menu.tex_val,
		env->menu.white, env->menu.tex_rect);
	ft_draw_slider(&env->menu, &env->menu.tex);
}
