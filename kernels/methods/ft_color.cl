#ifndef FT_COLOR_CL
# define FT_COLOR_CL

# include "../kernel.h"

t_color					ft_color_add_const(t_color c1, t_dec v1, const __constant t_color *c2, t_dec v2);
t_color					ft_color_add(t_color c1, t_dec v1, t_color c2, t_dec v2);
t_color					ft_color_bright_const(const __constant t_color *c, t_dec value);
t_color					ft_color_bright(t_color c, t_dec value);
t_vec3					ft_color_coeff(t_dec reflect, t_dec refract);

t_vec3					ft_color_coeff(t_dec reflect, t_dec refract)
{
	__private t_dec		tmp;
	__private t_dec		sum = reflect + refract;

	if (sum > 1)
	{
		tmp = (sum - 1) / 2;
		return ((t_vec3){reflect - tmp, refract - tmp, 0});
	}
	return ((t_vec3){reflect, refract, 1 - sum});

}

t_color					ft_color_bright(__private t_color c, t_dec value)
{
	__private int		k;
	__private int		l;

	k = -1;
	while (++k < 3)
	{
		l = c.byte[k] * value;
		c.byte[k] = (l > 255 ? 255 : l);
	}
	return (c);
}

t_color					ft_color_bright_const(const __constant t_color *c, t_dec value)
{
	__private int		k;
	__private int		l;
	__private t_color	cb;

	cb.byte[3] = c->byte[3];
	k = -1;
	while (++k < 3)
	{
		l = c->byte[k] * value;
		cb.byte[k] = (l > 255 ? 255 : l);
	}
	return (cb);
}

t_color					ft_color_add(__private t_color c1, t_dec v1,
									__private t_color c2, t_dec v2)
{
	__private int		k;
	__private int		l;

	k = -1;
	while (++k < 3)
	{
		l = c1.byte[k] * v1 + c2.byte[k] * v2;
		c1.byte[k] = (l > 255 ? 255 : l);
	}
	return (c1);
}

t_color					ft_color_add_const(__private t_color c1, t_dec v1,
									const __constant t_color *c2, t_dec v2)
{
	__private int		k;
	__private int		l;

	k = -1;
	while (++k < 3)
	{
		l = c1.byte[k] * v1 + (*c2).byte[k] * v2;
		c1.byte[k] = (l > 255 ? 255 : l);
	}
	return (c1);
}

#endif