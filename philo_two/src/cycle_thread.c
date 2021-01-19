/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 15:22:10 by abourbou          #+#    #+#             */
/*   Updated: 2021/01/19 20:22:43 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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
	while (kit->l_sem->nbr_fork_available < 2 && kit->vars->stop)
		sleep_with_one_eye(kit->vars, 1);
	sleep_with_one_eye(kit->vars, 1);
	sem_wait(kit->l_sem->s_fork);
	kit->l_sem->nbr_fork_available -= 1;
	philo_speak(kit, kit->vars->start_time, my_number, "has taken a fork");
	sem_wait(kit->l_sem->s_fork);
	kit->l_sem->nbr_fork_available -= 1;
	philo_speak(kit, kit->vars->start_time, my_number, "has taken a fork");
}

int		philo_eat(t_kit *kit, long my_number)
{
	philo_speak(kit, kit->vars->start_time, my_number, "is eating");
	sem_wait(kit->l_sem->s_meal);
	kit->vars->last_meal[my_number] = get_time();
	if (kit->vars->max_meal > 0)
		kit->vars->compt_meal[my_number] += 1;
	sem_post(kit->l_sem->s_meal);
	if (sleep_with_one_eye(kit->vars, kit->vars->time_to_eat))
		return (1);
	sem_post(kit->l_sem->s_fork);
	sem_post(kit->l_sem->s_fork);
	kit->l_sem->nbr_fork_available += 2;
	return (0);
}

void	*cycle_thread(void *vkit)
{
	t_kit	*kit;

	kit = vkit;
	sem_wait(kit->l_sem->s_meal);
	kit->vars->last_meal[kit->my_number] = get_time();
	sem_post(kit->l_sem->s_meal);
	while (!kit->vars->stop)
	{
		take_fork(kit, kit->my_number);
		if (philo_eat(kit, kit->my_number))
		{
			sem_post(kit->l_sem->s_fork);
			sem_post(kit->l_sem->s_fork);
			kit->l_sem->nbr_fork_available += 2;
			return (0);
		}
		philo_speak(kit, kit->vars->start_time, kit->my_number, "is sleeping");
		if (sleep_with_one_eye(kit->vars, kit->vars->time_to_sleep))
			return (0);
		philo_speak(kit, kit->vars->start_time, kit->my_number, "is thinking");
	}
	return (0);
}
