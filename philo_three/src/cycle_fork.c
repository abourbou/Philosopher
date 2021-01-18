/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_fork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 15:22:10 by abourbou          #+#    #+#             */
/*   Updated: 2021/01/18 23:28:10 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	philo_speak(t_kit *kit, long start_time, long my_number, char *message)
{
	sem_t	*speak;
	long	current_time;

	speak = kit->l_sem->s_speak;
	current_time = get_time() - start_time;
	sem_wait(speak);
	if (kit->vars->stop)
	{
		sem_post(speak);
		return ;
	}
	ft_putnbr(current_time / 1000);
	ft_putstr("ms    ");
	ft_putnbr(my_number + 1);
	ft_putstr("    ");
	ft_putstr(message);
	ft_putstr("\n");
	sem_post(speak);
}

void	take_fork(t_kit *kit, long my_number)
{
	sem_wait(kit->l_sem->s_pair_fork);
	sem_wait(kit->l_sem->s_fork);
	philo_speak(kit, kit->vars->start_time, my_number, "has taken a fork");
	sem_wait(kit->l_sem->s_fork);
	philo_speak(kit, kit->vars->start_time, my_number, "has taken a fork");
}

int		philo_eat(t_kit *kit, long my_number)
{
	philo_speak(kit, kit->vars->start_time, my_number, "is eating");
	kit->last_meal = get_time();
	kit->number_meal++;
	if (kit->vars->max_meal > 0 && kit->number_meal >= kit->vars->max_meal)	
		return (1);
	if (sleep_with_one_eye(kit->vars, kit->vars->time_to_eat))
		return (2);
	sem_post(kit->l_sem->s_fork);
	sem_post(kit->l_sem->s_fork);
	sem_post(kit->l_sem->s_pair_fork);
	return (0);
}

int		cycle_fork(void *vkit)
{
	t_kit		*kit;
	pthread_t	monitoring_pthread;
	int			return_val;

	kit = vkit;
	pthread_create(&monitoring_pthread, 0, monitoring_fork, vkit);
	kit->last_meal = get_time();
	while (!kit->vars->stop)
	{
		take_fork(kit, kit->my_number);
		if ((return_val = philo_eat(kit, kit->my_number)))
		{
			sem_post(kit->l_sem->s_fork);
			sem_post(kit->l_sem->s_fork);
			sem_post(kit->l_sem->s_pair_fork);
			return (return_val - 1);
		}
		philo_speak(kit, kit->vars->start_time, kit->my_number, "is sleeping");
		if (sleep_with_one_eye(kit->vars, kit->vars->time_to_sleep))
			return (1);
		philo_speak(kit, kit->vars->start_time, kit->my_number, "is thinking");
	}
	return (0);
}
