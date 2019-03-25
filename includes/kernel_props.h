/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: creep <creep@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 15:18:30 by dtheo             #+#    #+#             */
/*   Updated: 2018/07/23 13:46:45 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KERNEL_PROPS_H
# define KERNEL_PROPS_H

# define K_RT_NAME "ft_raytracer_base"
# define K_RT_PATH "./kernels/ft_raytracer.cl"
# define K_RT_ID 0

# define K_REF_NAME "ft_ref"
# define K_REF_PATH "./kernels/ft_ref.cl"
# define K_REF_ID 1

# define K_LIGHT_NAME "ft_raytracer_light"
# define K_LIGHT_PATH "./kernels/ft_light.cl"
# define K_LIGHT_ID 2

# define K_BLUR_NAME "ft_rt_blur"
# define K_BLUR_PATH "./kernels/ft_blur.cl"
# define K_BLUR_ID 3

# define K_GREYSCALE_NAME "ft_rt_greyscale"
# define K_GREYSCALE_PATH "./kernels/ft_greyscale.cl"
# define K_GREYSCALE_ID 4

# define K_SOBEL_NAME "ft_rt_sobel"
# define K_SOBEL_PATH "./kernels/ft_sobel.cl"
# define K_SOBEL_ID 5

# define K_TOON_LIGHT_NAME "ft_raytracer_light_toon"
# define K_TOON_LIGHT_PATH "./kernels/ft_light_toon.cl"
# define K_TOON_LIGHT_ID 6

# define K_COLOR_FILTER_NAME "ft_color_filter"
# define K_COLOR_FILTER_PATH "./kernels/ft_color_filter.cl"
# define K_COLOR_FILTER_ID 7

# define K_CYAN_FILTER_NAME "ft_cyan_filter"
# define K_CYAN_FILTER_PATH "./kernels/ft_cyan_filter.cl"
# define K_CYAN_FILTER_ID 8

# define K_NEGATIVE_NAME "ft_rt_negative"
# define K_NEGATIVE_PATH "./kernels/ft_negative.cl"
# define K_NEGATIVE_ID 9

# define K_SOBEL_DIR_NAME "ft_rt_sobel_dir"
# define K_SOBEL_DIR_PATH "./kernels/ft_sobel_dir.cl"
# define K_SOBEL_DIR_ID 10

# define K_CANNY_NAME "ft_rt_canny"
# define K_CANNY_PATH "./kernels/ft_canny.cl"
# define K_CANNY_ID 11

# define K_ANTIALIASING_NAME "ft_rt_antialiasing"
# define K_ANTIALIASING_PATH "./kernels/ft_antialiasing.cl"
# define K_ANTIALIASING_ID 12

# define K_SELECTOR_NAME "ft_selector"
# define K_SELECTOR_PATH "./kernels/ft_selector.cl"
# define K_SELECTOR_ID 13

# define K_TOTAL 14

#endif
