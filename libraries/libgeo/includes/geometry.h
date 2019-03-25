/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeigne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 17:27:44 by ppeigne           #+#    #+#             */
/*   Updated: 2018/06/21 16:37:30 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEOMETRY_H
# define GEOMETRY_H

/*
** INCLUDES
*/

# include <math.h>

/*
** DEFINE
*/

# define C_R 0
# define C_I 1

# define Q_W 0
# define Q_X 1
# define Q_Y 2
# define Q_Z 3

# define V_X 0
# define V_Y 1
# define V_Z 2

/*
** TYPEDEF
*/

typedef float	t_dec;

typedef t_dec	t_cpx[2];
typedef t_dec	t_quat[4];

typedef t_dec	t_vec[3];
typedef t_dec	t_mat[3][3];

/*
** PROTOTYPE
*/

void	ft_add_cpx(const t_cpx c1, const t_cpx c2, t_cpx res);
void	ft_sub_cpx(const t_cpx c1, const t_cpx c2, t_cpx res);
void	ft_cpx_mult(const t_cpx cpx1, const t_cpx cpx2, t_cpx result);
void	ft_cpx_to_power(const t_cpx cpx, const int power, t_cpx result);

void	ft_add_quat(const t_quat q1, const t_quat q2, t_quat res);
void	ft_sub_quat(const t_quat q1, const t_quat q2, t_quat res);
void	ft_quat_mult(const t_quat q1, const t_quat q2, t_quat res);
void	ft_init_quat_with_rot(const t_vec rot, t_quat res);

void	ft_quat_to_power(const t_quat q, int power, t_quat result);
void	ft_quat_to_mat(const t_quat q, t_dec mat[4][4]);
void	ft_mat_quat_mult(const t_dec mat[4][4], const t_quat quat, t_quat res);

void	ft_add_vec(const t_vec v0, const t_vec v1, t_vec res);
void	ft_sub_vec(const t_vec v0, const t_vec v1, t_vec res);
void	ft_scalar_mult(const t_vec v, const t_dec scalar, t_vec res);
t_dec	ft_dot_product(const t_vec v0, const t_vec v1);
void	ft_cross_product(const t_vec v0, const t_vec v1, t_vec product);

void	ft_normalize(const t_vec vec, t_vec res);
t_dec	ft_euclidean_norm(const t_vec vec);
void	ft_vec_to_quat(const t_vec vec, const t_dec angle, t_quat res);
void	ft_quat_vec_mult(const t_quat q, const t_vec v, t_vec res);
void	ft_mat_vec_mult(const t_mat trans, const t_vec vec, t_vec res);

void	ft_add_mat(const t_mat m1, const t_mat m2, t_mat res);
void	ft_sub_mat(const t_mat m1, const t_mat m2, t_mat res);
void	ft_mat_mult(const t_mat m1, const t_mat m2, t_mat res);
void	ft_set_identity(t_mat mat);

void	ft_x_rotation(const t_dec angle, t_mat m_rot);
void	ft_y_rotation(const t_dec angle, t_mat m_rot);
void	ft_z_rotation(const t_dec angle, t_mat m_rot);

void	ft_cpx_copy(const t_cpx c, t_cpx res);
void	ft_quat_copy(const t_quat q, t_cpx res);
void	ft_vec_copy(const t_vec v, t_cpx res);
void	ft_mat_copy(const t_mat m, t_mat res);

t_dec	ft_rad_to_deg(const t_dec rad);
t_dec	ft_deg_to_rad(const t_dec deg);

#endif
