/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtheo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 14:39:02 by dtheo             #+#    #+#             */
/*   Updated: 2018/08/21 14:39:03 by dtheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __KERNEL_H
# define __KERNEL_H

# define RT COCHON

# define X1 0
# define X2 1
# define Y1 2
# define Y2 3
# define SCALE 4
# define WEIGHT 5
# define C_R 6
# define C_I 7

# define R 0
# define I 1

# define RED 2
# define GREEN 1
# define BLUE 0
# define ALPHA 3

# define ID_SPHERE			0
# define ID_CONE			1
# define ID_PLANE			2
# define ID_CYLINDER		3
# define ID_CUBE			4

typedef float		t_dec;
typedef float4		t_quat;
typedef float3		t_vec3;
typedef float2		t_vec2;

typedef union		u_color
{
	int				rgb;
	unsigned char	byte[4];
	uchar4			byte4;
}					t_color;

typedef struct		s_tex
{
	t_color			*pixels;
	int				width;
	int				height;
	char			*name;
	void			*surface;
}					t_tex;

typedef struct		s_light
{
	t_vec3			pos;
	t_vec3			dir;

	t_dec			intensity;
	t_color			color;
	char			byte[8];
}					t_light;

typedef struct		s_obj
{
	t_vec3			pos;
	t_vec3			scl;
	t_vec3			dir;
	int				type;

	t_dec			spec;
	t_dec			trans;
	t_dec			refract;
	t_dec			reflect;
	char			texture;
	size_t			texture_scl;
	char			texture_norm;
	char			texture_spec;

	char			texture_mode;
	int				texture_xoff;
	int				texture_yoff;

	t_color			color;

	char			byte[12];
}					t_obj;

typedef struct		s_ray
{
	t_vec3			origin;
	t_vec3			dir;
	int				id;
	int				type;
	t_vec2			t;

	t_vec3			normal;
	t_vec3			p;
}					t_ray;

typedef struct		s_rt
{
	t_vec3			cam_pos;
	t_obj			*objs;
	t_light			*lights;
}					t_rt;

#endif
