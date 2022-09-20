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

static int	ft_minmax(int cnt, int znak, int num)
{
	if (cnt > 10 && znak == -1)
		return (0);
	else if (cnt > 10 && znak == 1)
		return (-1);
	return (num);
}

static int	ft_sign(int *i, char str, int znak)
{
	if (str == 45)
	{
		znak = znak * -1;
		*i = *i + 1;
	}
	if (str == 43)
		*i = *i + 1;
	return (znak);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	num;
	int	znak;
	int	cnt;

	cnt = 0;
	i = 0;
	znak = 1;
	num = 0;
	if (*str == '\0')
		return (0);
	while (str[i] < 14 || str[i] == 32)
		i++;
	if ((str[i] == 43 || str[i] == 45) && (str[i + 1] < 48 || str[i + 1] > 57))
		return (0);
	znak = ft_sign(&i, str[i], znak);
	while (str[i] > 47 && str[i] < 58)
	{
		num = num * 10 + (str[i] - '0');
		cnt++;
		i++;
	}
	num = ft_minmax(cnt, znak, num);
	return (num * znak);
}
