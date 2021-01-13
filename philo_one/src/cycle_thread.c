/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 15:22:10 by abourbou          #+#    #+#             */
/*   Updated: 2021/01/13 23:04:44 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	philo_speak(t_kit *kit, long start_time, long my_number, char *message)
{
	pthread_mutex_t *speak;
	long			current_time;

	if (kit->vars->stop)
		return ;
	speak = &kit->lmutex->m_speak;
	current_time = get_time() - start_time;
	pthread_mutex_lock(speak);
	ft_putnbr(current_time / 1000);
	ft_putstr("ms    ");
	ft_putnbr(my_number + 1);
	ft_putstr("    ");
	ft_putstr(message);
	ft_putstr("\n");
	pthread_mutex_unlock(speak);
}

void	take_fork(t_kit *kit, long my_number, long number_phil)
{
	long	left_fork;

	left_fork = (my_number == 0) ? number_phil - 1 : my_number - 1;
	while (kit->lmutex->is_fork_lock[my_number])
		usleep(1);
	kit->lmutex->is_fork_lock[left_fork] = 1;
	pthread_mutex_lock(&(kit->lmutex->m_fork[left_fork]));
	philo_speak(kit, kit->vars->start_time, my_number, "has taken left fork");
	kit->lmutex->is_fork_lock[my_number] = 1;
	pthread_mutex_lock(&(kit->lmutex->m_fork[my_number]));
	philo_speak(kit, kit->vars->start_time, my_number, "has taken right fork");
}

void	philo_eat(t_kit *kit, long my_number)
{
	long	left_fork;

	philo_speak(kit, kit->vars->start_time, my_number, "is eating");
	pthread_mutex_lock(&kit->lmutex->m_meal);
	kit->vars->last_meal[my_number] = get_time();
	pthread_mutex_unlock(&kit->lmutex->m_meal);
	usleep(kit->vars->time_to_eat * 1000);
	if (kit->vars->max_meal > 0)
	{
		pthread_mutex_lock(&kit->lmutex->m_meal);
		kit->vars->compt_meal[my_number] += 1;
		pthread_mutex_unlock(&kit->lmutex->m_meal);
	}
	left_fork = (my_number == 0) ? kit->vars->number_phil - 1 : my_number - 1;
	kit->lmutex->is_fork_lock[left_fork] = 0;
	pthread_mutex_unlock(&kit->lmutex->m_fork[left_fork]);
	kit->lmutex->is_fork_lock[my_number] = 0;
	pthread_mutex_unlock(&kit->lmutex->m_fork[my_number]);
}

void	*cycle_thread(void *vkit)
{
	t_kit	*kit;

	kit = vkit;
	pthread_mutex_lock(&(kit->lmutex->m_meal));
	kit->vars->last_meal[kit->my_number] = get_time();
	pthread_mutex_unlock(&(kit->lmutex->m_meal));

	take_fork(kit, kit->my_number, kit->vars->number_phil);
	philo_eat(kit, kit->my_number);
	philo_speak(kit, kit->vars->start_time, kit->my_number, "is sleeping");
	//usleep(kit->vars->time_to_sleep * 1000);
	if (sleep_with_one_eye(kit->vars, kit->vars->time_to_sleep))
		return (0);
	philo_speak(kit, kit->vars->start_time, kit->my_number, "is thinking");

	return (0);
}
