/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_rt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppeigne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 18:53:11 by ppeigne           #+#    #+#             */
/*   Updated: 2018/08/20 18:53:58 by ppeigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#if defined __APPLE__
# if defined CLOCK_MONOTONIC

static t_dec	ft_get_time(void)
{
	struct timespec		get_time;

	clock_gettime(CLOCK_MONOTONIC, &get_time);
	return (get_time.tv_sec + get_time.tv_nsec / BILLION);
}

# else

static t_dec	ft_get_time(void)
{
	clock_serv_t			cclock;
	mach_timespec_t			mts;

	host_get_clock_service(mach_host_self(), REALTIME_CLOCK, &cclock);
	clock_get_time(cclock, &mts);
	mach_port_deallocate(mach_task_self(), cclock);
	return (mts.tv_nsec / BILLION + mts.tv_sec);
}

# endif
#elif defined __linux__

static t_dec	ft_get_time(void)
{
	struct timespec		get_time;

	clock_gettime(CLOCK_MONOTONIC, &get_time);
	return (get_time.tv_sec + get_time.tv_nsec / BILLION);
}

#else

static t_dec	ft_get_time(void)
{
	static LARGE_INTEGER	frequency;
	LARGE_INTEGER			now;

	if (frequency.QuadPart == 0)
		QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&now);
	return (now.QuadPart / (t_dec)(frequency.QuadPart));
}

#endif

void			ft_compute_rt(t_env *env, t_rt_param *param)
{
	t_dec			time;

	ft_check_stereo(param);
	ft_init_rt(env, param);
	time = ft_get_time();
	clEnqueueNDRangeKernel(*env->ocl_rt.queue,
			env->ocl_rt.kernel[K_RT_ID], 1, NULL,
			&param->mem_objs.size, NULL, 0, NULL, NULL);
	clFinish(*env->ocl_rt.queue);
	if (ft_get_time() - time > 0.25 - param->r_limit * 0.03)
		ft_display_load(env);
	ft_init_border(env, param);
	ft_compute_rt_border(env, param);
	ft_compute_rt_light(env, param);
	ft_compute_rt_ref(env, param);
	ft_init_antialiasing(env, param);
	ft_compute_rt_antialiasing(env, param);
	ft_init_postprocess(env, param);
	ft_compute_rt_postprocess(env, param);
	ft_stereo(env, param);
	if (param->border == 1)
		SDL_BlitSurface(param->lay_border, NULL, param->lay_rt, NULL);
}
