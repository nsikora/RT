/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_fps_limiter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbard <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 18:45:01 by jbard             #+#    #+#             */
/*   Updated: 2018/08/20 18:45:03 by jbard            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** ft_get_time:
**
** Give the time in second (with decimal).
**
** The function use 'clock_gettime()' on linux
** and MACOS and 'QueryPerformanceFrequency()'
** on Windows.
*/

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

/*
** ft_event_fps_limiter:
**
** Limit frame per seconds to 'max_fps'.
**
** The function use 'ft_get_time()' to
** calculate exact time passed on CPU
** AND GPU.
**
** IF the step between two function call
** is to small the function return '0'.
** ELSE the function return '1' and
** increase by one the number of FPS.
**
** When a second pass ('gap' > 1) the
** function reset FPS count.
*/

int				ft_event_fps_limiter(t_env *env)
{
	static t_dec	last_second = 0;
	static int		fps;
	t_dec			gap;

	gap = ft_get_time() - last_second;
	if (gap > 1)
	{
		if (env->menu.menu == 0)
		{
			env->param.merge_layers = 1;
			env->param.fps = fps;
		}
		fps = 0;
		last_second = ft_get_time();
	}
	if (gap < (t_dec)fps / env->param.max_fps)
		return (0);
	fps++;
	return (1);
}
