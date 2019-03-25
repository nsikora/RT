/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slider.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeigne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 18:08:41 by ppeigne           #+#    #+#             */
/*   Updated: 2018/08/20 18:08:43 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ft_draw_slider(t_menu *menu, t_slider *s)
{
	size_t	coor[4];

	coor[0] = s->coor[0];
	coor[1] = s->coor[1] - s->thick / 2;
	coor[2] = coor[0] + s->length;
	coor[3] = coor[1] + s->thick;
	ft_draw_square(coor, (int *)menu->lay_base->pixels,
		menu->lay_base->w, s->empty.rgb);
	coor[0] += 2;
	coor[1] += 2;
	coor[2] = coor[0] + (s->length - 2) *
		((s->val - s->min) / (s->max - s->min)) - 2;
	coor[3] -= 2;
	ft_draw_square(coor, (int *)menu->lay_base->pixels,
		menu->lay_base->w, s->fill.rgb);
}

void		ft_update_slider(t_menu *menu, t_slider *s,
							SDL_Rect rect, size_t pos)
{
	s->thick = menu->button_coor[pos].h - menu->button_coor[pos].y;
	s->thick *= 0.2;
	s->coor[0] = menu->sub_menu_coor[0] + 10;
	s->coor[1] = rect.y + rect.h + s->thick / 2 + 5;
	s->length = (menu->sub_menu_coor[2] - 10);
	s->length -= (menu->sub_menu_coor[0] + 10);
}

void		ft_update_all_sliders(t_menu *menu)
{
	ft_update_slider_color(menu);
	ft_update_slider(menu, &menu->fov, menu->fov_rect, 6);
	ft_update_slider(menu, &menu->trans, menu->trans_rect, 4);
	ft_update_slider(menu, &menu->refraction, menu->refract_rect, 5);
	ft_update_slider(menu, &menu->reflection, menu->reflect_rect, 3);
	ft_update_slider(menu, &menu->spec, menu->spec_rect, 2);
	ft_update_slider(menu, &menu->ambient, menu->ambient_rect, 3);
	ft_update_slider(menu, &menu->tex, menu->tex_rect, 3);
	ft_update_slider(menu, &menu->tex_scl, menu->tex_scl_rect, 4);
}

void		ft_init_all_sliders(t_env *env)
{
	ft_init_slider_color(&env->menu);
	ft_init_slider_fov(&env->menu);
	ft_init_slider_trans(&env->menu);
	ft_init_slider_refract(&env->menu);
	ft_init_slider_reflect(&env->menu);
	ft_init_slider_spec(&env->menu);
	ft_init_slider_ambient(env, &env->menu);
	ft_init_slider_tex(env, &env->menu);
	ft_init_slider_tex_scl(&env->menu);
}

int			ft_event_slider(t_env *env, t_slider *slider, size_t x, size_t y)
{
	size_t	coor2[2];
	float	new_val;

	coor2[0] = slider->coor[0] + slider->length;
	coor2[1] = slider->coor[1] - slider->thick / 2;
	if (x > slider->coor[0] && x < coor2[0]
		&& y > coor2[1] && y < coor2[1] + slider->thick)
	{
		new_val = x - slider->coor[0];
		if (new_val < 2)
			new_val = slider->min;
		else if (new_val > slider->length - 2)
			new_val = slider->max;
		else
			new_val = (new_val - 2) / (slider->length - 2)
				* (slider->max - slider->min) + slider->min;
		slider->val = new_val;
		env->param.menu_change = 1;
		env->menu.redraw = 1;
		return (1);
	}
	return (0);
}
