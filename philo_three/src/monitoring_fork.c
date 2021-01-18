/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_fork.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 11:28:48 by abourbou          #+#    #+#             */
/*   Updated: 2021/01/18 22:13:58 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*monitoring_fork(void *pkit)
{
	t_kit	*kit;
	long	elapse_time;

	kit = pkit;
	while(kit->last_meal == 0)
		usleep(1000);

	while (elapse_time < kit->vars->time_to_die)
	{
		usleep(1000);
		elapse_time = get_time() - kit->last_meal;
	}
	kit->vars->stop = 1;
	return (0);
}
