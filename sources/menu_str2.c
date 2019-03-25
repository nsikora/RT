/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_str2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtheo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 08:37:13 by dtheo             #+#    #+#             */
/*   Updated: 2018/08/21 08:37:15 by dtheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char	*ft_str_percentage(t_dec val)
{
	char	*str;
	char	*tmp;
	size_t	len;

	tmp = ft_itoa(val * 100);
	len = ft_strlen(tmp) + 2;
	if (!(str = ft_strnew(len)))
		return (NULL);
	ft_strcpy(str, tmp);
	str[len - 2] = '%';
	free(tmp);
	return (str);
}

void	ft_compute_menu_str_pos_part5(t_env *env)
{
	ft_compute_str_ambient(env);
	ft_compute_str_fov(env);
	ft_compute_str_reflect(env);
	ft_compute_str_refract(env);
	ft_compute_str_spec(env);
	ft_compute_str_trans(env);
	ft_compute_str_tex(env);
	ft_compute_str_tex_scl(env);
}

void	ft_compute_menu_str_pos_part4(t_env *env, int width, int height)
{
	if (env->rt_param.mem_objs.nb_obj > 2)
		TTF_SizeText(env->pt_mono, "OBJECTS  ", &width, &height);
	else
		TTF_SizeText(env->pt_mono, "OBJECT  ", &width, &height);
	if (env->menu.objects_val)
		free(env->menu.objects_val);
	env->menu.objects_val = ft_itoa(env->rt_param.mem_objs.nb_obj - 1);
	env->menu.objects_rect = (SDL_Rect){env->menu.sub_menu_coor[0] + width,
		env->menu.str_rect[4].y, 0, 0};
	if (env->rt_param.mem_objs.nb_light > 2)
		TTF_SizeText(env->pt_mono, "LIGHTS  ", &width, &height);
	else
		TTF_SizeText(env->pt_mono, "LIGHT  ", &width, &height);
	if (env->menu.lights_val)
		free(env->menu.lights_val);
	env->menu.lights_val = ft_itoa(env->rt_param.mem_objs.nb_light - 1);
	env->menu.lights_rect = (SDL_Rect){env->menu.sub_menu_coor[0] + width,
		env->menu.str_rect[5].y, 0, 0};
	TTF_SizeText(env->pt_mono, "REFLECT  ", &width, &height);
	if (env->menu.limit_val)
		free(env->menu.limit_val);
	env->menu.limit_val = ft_itoa(env->rt_param.r_limit);
	env->menu.limit_rect = (SDL_Rect){env->menu.sub_menu_coor[0] + width,
		env->menu.str_rect[6].y, 0, 0};
	ft_compute_menu_str_pos_part5(env);
}

void	ft_draw_menu_str_info2(t_env *env)
{
	if (env->rt_param.mem_objs.nb_obj > 2)
		ft_ttf_render_txt_b_menu(env, "OBJECTS  ", env->menu.orange,
		env->menu.str_rect[4]);
	else
		ft_ttf_render_txt_b_menu(env, "OBJECT  ", env->menu.orange,
		env->menu.str_rect[4]);
	ft_ttf_render_txt_b_menu(env, env->menu.objects_val,
	env->menu.white, env->menu.objects_rect);
	if (env->rt_param.mem_objs.nb_light > 2)
		ft_ttf_render_txt_b_menu(env, "LIGHTS  ", env->menu.orange,
		env->menu.str_rect[5]);
	else
		ft_ttf_render_txt_b_menu(env, "LIGHT  ", env->menu.orange,
		env->menu.str_rect[5]);
	ft_ttf_render_txt_b_menu(env, env->menu.lights_val,
	env->menu.white, env->menu.lights_rect);
}

void	ft_draw_menu_str_filter(t_env *env)
{
	static const char *str_filter[] = {"RED", "LIME", "BLUE"};

	if (env->preview_param.post == P_COLOR)
	{
		ft_ttf_render_txt_b_menu(env, str_filter[(int)env->preview_param.color],
		env->menu.filter_color[(int)env->preview_param.color],
		env->menu.fps_rect);
	}
	else if (env->preview_param.post == P_GREY)
	{
		ft_ttf_render_txt_b_menu(env, "GREY", env->menu.grey,
			env->menu.fps_rect);
	}
	else if (env->preview_param.post == P_NEG)
	{
		ft_ttf_render_txt_b_menu(env, "NEG", env->menu.violet,
			env->menu.fps_rect);
	}
	else
	{
		ft_ttf_render_txt_b_menu(env, "NONE", env->menu.white,
			env->menu.fps_rect);
	}
}
