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

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo
{
	pthread_t			thread;
	int					num;
	int					left;
	int					right;
	int					eatcnt;
	long long			last_eat_time;
	struct s_timings	*tm;
}				t_philo;

typedef struct s_timings
{
	int				phnum;
	int				die;
	int				eat;
	int				sleep;
	int				numeat;
	long long		start;
	int				dead;
	int				all_eat;
	pthread_mutex_t	forks[300];
	pthread_mutex_t	print;
	t_philo			philos[300];
}				t_timings;

int			threads_create(t_timings *tm);
long long	get_time(void);
int			ft_atoi(const char *str);
void		time_stop(t_timings *tm, long long t2s);
void		printing(t_timings *tm, int num, char *str, long long time);

#endif
