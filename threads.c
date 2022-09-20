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

void	peat(t_philo *ph)
{
	t_timings	*tm;
	long long	cur_time;

	tm = ph->tm;
	if (tm->dead == 1)
		return ;
	pthread_mutex_lock(&tm->forks[ph->left]);
	cur_time = get_time() - tm->start;
	printing(tm, ph->num, "has taken a fork", cur_time);
	if (tm->phnum < 2)
		return ;
	pthread_mutex_lock(&tm->forks[ph->right]);
	cur_time = get_time() - tm->start;
	printing(tm, ph->num, "has taken a fork", cur_time);
	cur_time = get_time() - tm->start;
	printing(tm, ph->num, "is eating", cur_time);
	ph->last_eat_time = get_time();
	time_stop(tm, tm->eat);
	tm->philos[ph->num].eatcnt = tm->philos[ph->num].eatcnt + 1;
	pthread_mutex_unlock(&tm->forks[ph->left]);
	pthread_mutex_unlock(&tm->forks[ph->right]);
}

void	*phlife(void *philo)
{
	t_timings	*tm;
	long long	cur_time;

	tm = ((t_philo *)philo)->tm;
	if (((t_philo *)philo)->num % 2)
		usleep(10000);
	while (tm->dead == 0)
	{
		peat((t_philo *)philo);
		if (tm->phnum < 2 || tm->all_eat)
			break ;
		cur_time = get_time() - tm->start;
		printing(tm, ((t_philo *)philo)->num, "is sleeping", cur_time);
		time_stop(tm, tm->sleep);
		cur_time = get_time() - tm->start;
		printing(tm, ((t_philo *)philo)->num, "is thinking", cur_time);
	}
	return (0);
}

void	philo_status(t_timings *tm)
{
	int	i;

	while (tm->all_eat == 0)
	{
		i = -1;
		while (++i < tm->phnum && !tm->dead)
		{
			if (get_time() - tm->philos[i].last_eat_time > tm->die)
			{
				printing(tm, i, "died", get_time() - tm->start);
				tm->dead = 1;
			}
			usleep(100);
		}
		if (tm->dead == 1)
			break ;
		i = 0;
		while (tm->numeat != -1 && i < tm->phnum
			&& tm->philos[i].eatcnt >= tm->numeat)
			i++;
		if (i >= tm->phnum - 1 && tm->phnum > 1)
			tm->all_eat = 1;
	}
}

void	threads_join(t_timings *tm)
{
	int	i;

	i = 0;
	while (i < tm->phnum)
	{
		pthread_join(tm->philos[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < tm->phnum)
	{
		pthread_mutex_destroy(&tm->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&tm->print);
}

int	threads_create(t_timings *tm)
{
	int	i;

	tm->start = get_time();
	i = 0;
	while (i < tm->phnum)
	{
		if (pthread_create(&tm->philos[i].thread, NULL, phlife, &tm->philos[i]))
			return (1);
		tm->philos[i].last_eat_time = get_time();
		i++;
	}
	philo_status(tm);
	threads_join(tm);
	return (0);
}
