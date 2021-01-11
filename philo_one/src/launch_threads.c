/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 10:42:10 by abourbou          #+#    #+#             */
/*   Updated: 2021/01/11 11:44:37 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"


void	destroy_arr_kit(t_kit **tab_kit)
{
	int i;

	i = 0;
	while (tab_kit[i])
	{
		free(tab_kit[i]);
		i++;
	}
	free(tab_kit);
}

static t_kit	**init_arr_kit(int number_phil, t_vars *global_var, t_lmutex *lst_mutex)
{
	t_kit	**arr_kit;
	t_kit	*kit;

	int	i;

	if (!(arr_kit = malloc((global_var->number_phil + 1) * sizeof(t_kit))))
		return (0);
	memset(arr_kit, 0, (global_var->number_phil + 1) * sizeof(t_kit));
	i = 0;
	while (i < number_phil)
	{
		if (!(kit = malloc(sizeof(t_kit))))
		{	
			destroy_arr_kit(arr_kit);
			return (0);
		}
		arr_kit[i] = kit;
		kit->vars = global_var;
		kit->lmutex = lst_mutex;
		kit->my_number = i;
		kit->number_meal = 0;
		i++;
	}
	return (arr_kit);
}

int		launch_threads(t_vars *global_var, t_lmutex *lst_mutex, int number_phil)
{
	int			i;
	t_kit		**arr_kit;
	pthread_t	*arr_thread;

	if (!(arr_kit = init_arr_kit(number_phil, global_var, lst_mutex)))
		return (0);
	if (!(arr_thread = malloc(sizeof(pthread_t) * (number_phil + 1))))
	{
		destroy_arr_kit(arr_kit);
		return (0);
	}
	pthread_create(&arr_thread[number_phil + 1], 0, monitoring_threads, global_var);
	i = 0;
	while (i < number_phil)
	{
		pthread_create(&arr_thread[i], 0, start_pthread, arr_kit[i]);
		//sleep(1);
		i++;
	}
	pthread_join(arr_thread[number_phil + 1], 0);
	i = 0;
	while (i < number_phil)
	{
		pthread_join(arr_thread[i], 0);
		i++;
	}
	destroy_arr_kit(arr_kit);
	free(arr_thread);
	return (1);
}