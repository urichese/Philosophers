/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: urichese <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 19:50:04 by urichese          #+#    #+#             */
/*   Updated: 2021/04/22 19:51:42 by urichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	a;

	gettimeofday(&a, DST_NONE);
	return ((a.tv_sec * 1000) + a.tv_usec / 1000);
}

void	time_stop(t_timings *tm, long long t2a)
{
	long long	time;

	time = get_time();
	while (tm->dead == 0)
	{
		if ((get_time() - time) >= t2a)
			break ;
		usleep(100);
	}
}

void	printing(t_timings *tm, int num, char *str, long long time)
{
	pthread_mutex_lock(&tm->print);
	if (tm->dead == 0)
		printf("%lld %d %s\n", time, num + 1, str);
	pthread_mutex_unlock(&tm->print);
}
