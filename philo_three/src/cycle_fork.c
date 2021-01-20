/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_fork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 15:22:10 by abourbou          #+#    #+#             */
/*   Updated: 2021/01/20 09:22:48 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	philo_speak(t_kit *kit, long my_number, char *message, int is_last)
{
	sem_t	*speak;
	long	current_time;
	long	start_time;

	speak = kit->l_sem->s_speak;
	start_time = kit->vars->start_time;
	current_time = get_time() - start_time;
	sem_wait(speak);
	ft_putnbr(current_time / 1000);
	ft_putstr("ms    ");
	ft_putnbr(my_number + 1);
	ft_putstr("    ");
	ft_putstr(message);
	ft_putstr("\n");
	if (!is_last)
		sem_post(speak);
}

void	take_fork(t_kit *kit, long my_number)
{
	sem_wait(kit->l_sem->s_pair_fork);
	sem_wait(kit->l_sem->s_fork);
	philo_speak(kit, my_number, "has taken a fork", 0);
	sem_wait(kit->l_sem->s_fork);
	philo_speak(kit, my_number, "has taken a fork", 0);
}

int		philo_eat(t_kit *kit, long my_number)
{
	sem_wait(kit->l_sem->s_eating);
	philo_speak(kit, my_number, "is eating", 0);
	kit->last_meal = get_time();
	sem_post(kit->l_sem->s_eating);
	kit->number_meal++;
	if (kit->vars->max_meal > 0 && kit->number_meal >= kit->vars->max_meal)
		return (1);
	usleep(kit->vars->time_to_eat * 1000);
	sem_post(kit->l_sem->s_fork);
	sem_post(kit->l_sem->s_fork);
	sem_post(kit->l_sem->s_pair_fork);
	return (0);
}

int		cycle_fork(void *vkit)
{
	t_kit		*kit;
	pthread_t	monitoring_pthread;

	kit = vkit;
	kit->last_meal = get_time();
	pthread_create(&monitoring_pthread, 0, monitoring_fork, vkit);
	while (1)
	{
		take_fork(kit, kit->my_number);
		if (philo_eat(kit, kit->my_number))
		{
			sem_post(kit->l_sem->s_fork);
			sem_post(kit->l_sem->s_fork);
			sem_post(kit->l_sem->s_pair_fork);
			exit(0);
		}
		philo_speak(kit, kit->my_number, "is sleeping", 0);
		usleep(kit->vars->time_to_sleep * 1000);
		philo_speak(kit, kit->my_number, "is thinking", 0);
	}
	return (1);
}
