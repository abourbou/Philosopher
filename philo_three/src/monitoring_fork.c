/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_fork.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 11:28:48 by abourbou          #+#    #+#             */
/*   Updated: 2021/01/19 14:46:04 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*monitoring_fork(void *pkit)
{
	t_kit	*kit;
	long	elapse_time;

	kit = pkit;
	elapse_time = 0;
	while (kit->last_meal == 0)
		usleep(1000);
	while (elapse_time < kit->vars->time_to_die)
	{
		usleep(1000);
		elapse_time = (get_time() - kit->last_meal) / 1000;
	}
	philo_speak(kit, kit->my_number, "died", 1);
	exit(1);
}
