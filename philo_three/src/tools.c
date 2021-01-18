/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 10:39:11 by abourbou          #+#    #+#             */
/*   Updated: 2021/01/18 23:17:31 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo_three.h"

void	ft_putstr(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	write(1, str, i);
}

long	ft_atoi(char *str)
{
	int		i;
	long	number;

	i = 0;
	number = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = number * 10;
		number += (long)(str[i] - '0');
		i++;
	}
	return (number);
}

void	ft_putnbr(long nbr)
{
	char	c;

	if (nbr < 10)
	{
		c = nbr + '0';
		write(1, &c, 1);
	}
	else
	{
		ft_putnbr(nbr / 10);
		ft_putnbr(nbr % 10);
	}
}

long	get_time(void)
{
	struct timeval	scurrent_time;
	long			current_time;

	gettimeofday(&scurrent_time, NULL);
	current_time = scurrent_time.tv_sec * 1000000 + scurrent_time.tv_usec;
	return (current_time);
}

long	sleep_with_one_eye(t_vars *glob_var, long time_sleep)
{
	long	start_time;
	long	current_time;

	start_time = get_time();
	current_time = 0;
	while (!glob_var->stop && current_time < time_sleep)
	{
		usleep(1000);
		current_time = (get_time() - start_time) / 1000;
	}
	return (glob_var->stop);
}
