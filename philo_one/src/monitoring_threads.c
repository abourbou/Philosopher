/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_threads.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 11:28:48 by abourbou          #+#    #+#             */
/*   Updated: 2021/01/13 22:44:33 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		is_maxmeal(t_vars *glob_var, long max_meal)
{
	long	i;
	int		is_over;

	if (max_meal <= 0)
		return (0);
	i = 0;
	is_over = 1;
	while (i < glob_var->number_phil)
	{
		if (glob_var->compt_meal[i] < glob_var->max_meal)
		{
			is_over = 0;
			break;
		}
		i++;
	}
	return (is_over);
	return (0);
}

int		is_dead(t_kit *kit)
{
	int		i;
	long	start_time;

	i = 0;
	start_time = kit->vars->start_time;
	while (i < kit->vars->number_phil)
	{
		if (get_time() - kit->vars->last_meal[i] >= kit->vars->time_to_die * 1000)
		{
			philo_speak(kit, start_time, i, "died");
			return (1);
		}
		i++;
	}
	return (0);
}

void	*monitoring_threads(void *pkit)
{/*
	t_kit *kit;

	kit = pkit;
	while (!is_dead(kit) && !is_maxmeal(kit->vars, kit->vars->max_meal))
		usleep(1000);
	kit->vars->stop = 1;
	return (0);
*/
	(void)pkit;
	return (0);
}