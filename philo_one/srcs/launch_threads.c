/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 17:02:58 by abourbou          #+#    #+#             */
/*   Updated: 2020/12/23 20:12:14 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*thread_function(void *vkit)
{
	t_kit	*kit;

	kit = vkit;
	
	free(kit);
	return (0);
}

/*
**	return 1 if success or 0 if fail
*/

int		launch_threads(t_args *args, t_mutex *mutex)
{
	int			i;
	pthread_t	*tab_thread;
	t_kit		*kit;

	i = 0;
	if (!(tab_thread = malloc(sizeof(pthread_t) * args->nbr_philo)))
		return (0);
	while (i < args->nbr_philo)
	{
		if (!(kit = malloc(sizeof(t_kit))))
			return (0);
		kit->args = args;
		kit->mutex = mutex;
		kit->serial_number = i + 1;
		kit->forks[0] = i;
		kit->forks[1] = (i + 1 == args->nbr_philo) ? 0 : i + 1;
		pthread_create(&tab_thread[i], NULL, thread_function, kit);
		i++;
	}
	i = 0;
	while (i < args->nbr_philo)
	{
		pthread_join(tab_thread[i], NULL);
		i++;
	}
	return (1);
}