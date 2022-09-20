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

void	philos_fill(t_timings *tm)
{
	int	i;

	i = 0;
	while (i < tm->phnum)
	{
		tm->philos[i].num = i;
		tm->philos[i].left = i;
		tm->philos[i].right = (i + 1) % tm->phnum;
		tm->philos[i].eatcnt = 0;
		tm->philos[i].last_eat_time = 0;
		tm->philos[i].tm = tm;
		i++;
	}
}

int	mut_set(t_timings *tm)
{
	int	i;

	i = 0;
	while (i < tm->phnum)
	{
		if (pthread_mutex_init(&tm->forks[i], NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&tm->print, NULL))
		return (1);
	return (0);
}

int	settings(t_timings *tm, char **argv, int argc)
{
	tm->phnum = ft_atoi(argv[1]);
	tm->die = ft_atoi(argv[2]);
	tm->eat = ft_atoi(argv[3]);
	tm->sleep = ft_atoi(argv[4]);
	if (argc == 6)
		tm->numeat = ft_atoi(argv[5]);
	else
		tm->numeat = -1;
	if (tm->phnum < 0 || tm->die < 0 || tm->eat < 0
		|| tm->sleep < 0 || (argc == 6 && tm->numeat < 0))
		return (1);
	tm->dead = 0;
	tm->all_eat = 0;
	philos_fill(tm);
	if (mut_set(tm))
		return (2);
	return (0);
}

int	main(int argc, char **argv)
{
	t_timings	tm;
	int			err;

	if (argc < 5 || argc > 6)
	{
		printf ("Wrong number of argument\n");
		return (1);
	}
	err = settings(&tm, argv, argc);
	if (err == 1)
	{
		printf ("Wrong argument value\n");
		return (2);
	}
	if (err == 2)
	{
		printf ("Mutex error\n");
		return (3);
	}
	if (threads_create(&tm))
	{
		printf("Thread create error\n");
		return (4);
	}
}
