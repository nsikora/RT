/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeigne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 18:46:37 by ppeigne           #+#    #+#             */
/*   Updated: 2018/08/21 12:59:58 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	ft_compute_menu_str_pos_part3(t_env *env, int width, int height)
{
	env->menu.fps_rect = (SDL_Rect){env->menu.sub_menu_coor[0] +
		(env->menu.size_of_char[0] * 4), env->menu.str_rect[1].y, 0, 0};
	TTF_SizeText(env->pt_mono, "WIDTH  ", &width, &height);
	if (env->menu.width_val)
		free(env->menu.width_val);
	env->menu.width_val = ft_itoa(env->param.width);
	env->menu.width_rect = (SDL_Rect){env->menu.sub_menu_coor[0] + width,
		env->menu.str_rect[2].y, 0, 0};
	TTF_SizeText(env->pt_mono, "HEIGHT  ", &width, &height);
	if (env->menu.height_val)
		free(env->menu.height_val);
	env->menu.height_val = ft_itoa(env->param.height);
	env->menu.height_rect = (SDL_Rect){env->menu.sub_menu_coor[0] + width,
		env->menu.str_rect[3].y, 0, 0};
	ft_compute_menu_str_pos_part4(env, width, height);
}

static void	ft_compute_menu_str_pos_part2(t_env *env, const int center,
	int width, int height)
{
	int			i;

	TTF_SizeText(env->pt_mono, STR_INFO, &width, &height);
	env->menu.titles_pos[0][0] = center - width / 2;
	TTF_SizeText(env->pt_mono, STR_EDIT, &width, &height);
	env->menu.titles_pos[2][0] = center - width / 2;
	TTF_SizeText(env->pt_mono, STR_PARAM, &width, &height);
	env->menu.titles_pos[3][0] = center - width / 2;
	TTF_SizeText(env->pt_mono, STR_LOAD, &width, &height);
	env->menu.loading_pos[0] = env->menu.rt_rect.x + env->menu.rt_rect.w / 2
	- width / 2;
	env->menu.loading_pos[1] = env->param.height / 2 - height / 2;
	height = -height / 2 + env->menu.button_coor[0].h / 2;
	i = -1;
	env->menu.str_rect[0].x = env->menu.sub_menu_coor[0] + 10;
	while (++i < 7)
	{
		env->menu.str_rect[i].x = env->menu.str_rect[0].x;
		env->menu.str_rect[i].y = height + env->menu.button_coor[i].y;
	}
	TTF_SizeText(env->pt_mono, "A", &env->menu.size_of_char[0],
	&env->menu.size_of_char[0]);
	ft_compute_menu_str_pos_part3(env, width, height);
}

static void	ft_compute_menu_str_pos(t_env *env, int width, int height)
{
	const int	center = (int)(2. / 16. * env->param.width);
	const int	width_max = env->menu.rt_rect.x - env->menu.menu_coor[2];
	int			size;

	size = 42;
	ft_ttf_open_font(&env->pt_mono, PT_MONO_PATH, size);
	TTF_SizeText(env->pt_mono, STR_POST, &width, &height);
	while ((width > width_max || height > (int)env->menu.button_coor[0].h)
			&& size > 1)
	{
		ft_ttf_close_font(&env->pt_mono);
		size--;
		ft_ttf_open_font(&env->pt_mono, PT_MONO_PATH, size);
		TTF_SizeText(env->pt_mono, STR_POST, &width, &height);
	}
	env->menu.titles_pos[0][1] = (int)(0.5 / 9. * env->param.height)
		- height / 2;
	env->menu.titles_pos[1][1] = env->menu.titles_pos[0][1];
	env->menu.titles_pos[2][1] = env->menu.titles_pos[0][1];
	env->menu.titles_pos[3][1] = env->menu.titles_pos[0][1];
	env->menu.titles_pos[1][0] = center - width / 2;
	ft_compute_menu_str_pos_part2(env, center, width, height);
}

static void	ft_compute_button_option_pos(t_env *env)
{
	int i;

	env->menu.button_coor[0].w = env->menu.menu_coor[2];
	env->menu.button_coor[0].h = (size_t)(1. / 9. * env->param.height);
	env->menu.logo_coor[0].x = 7;
	env->menu.logo_coor[0].y = 10;
	env->menu.logo_coor[0].w = env->menu.button_coor[0].w - 15;
	env->menu.logo_coor[0].h = env->menu.button_coor[0].h - 15;
	i = 0;
	while (++i < 7)
	{
		env->menu.button_coor[i].y = env->menu.button_coor[i - 1].h;
		env->menu.button_coor[i].w = env->menu.menu_coor[2];
		env->menu.button_coor[i].h = (size_t)((float)(i + 1) / 9. *
			env->param.height);
		env->menu.logo_coor[i].x = 7;
		env->menu.logo_coor[i].y = env->menu.button_coor[i].y + 5;
		env->menu.logo_coor[i].w = env->menu.logo_coor[0].w;
		env->menu.logo_coor[i].h = env->menu.logo_coor[0].h;
		env->menu.option_rect[i] = (SDL_Rect){env->menu.button_coor[i].w,
			env->menu.button_coor[i].y, 0, 0};
	}
}

void		ft_compute_menu_pos(t_env *env)
{
	env->menu.redraw = 1;
	env->menu.rt_rect.x = (int)(3. / 16. * env->param.width);
	env->menu.rt_rect.w = (int)env->param.width - env->menu.rt_rect.x;
	env->menu.rt_rect.h = (int)env->param.height;
	env->menu.info_coor[0] = (size_t)(13. / 16. * env->param.width);
	env->menu.info_coor[1] = (size_t)(7. / 9. * env->param.height);
	env->menu.info_coor[2] = env->param.width;
	env->menu.info_coor[3] = env->param.height;
	env->menu.preview_rect.y = env->menu.info_coor[1];
	env->menu.preview_rect.w = env->menu.rt_rect.x;
	env->menu.preview_rect.h = env->param.height - env->menu.preview_rect.y;
	env->menu.menu_coor[2] = (size_t)(1. / 16. * env->param.width);
	env->menu.menu_coor[3] = env->menu.info_coor[1];
	env->menu.sub_menu_coor[0] = env->menu.menu_coor[2];
	env->menu.sub_menu_coor[2] = env->menu.rt_rect.x;
	env->menu.sub_menu_coor[3] = env->menu.info_coor[1];
	ft_compute_button_option_pos(env);
	ft_compute_menu_str_pos(env, 0, 0);
}
