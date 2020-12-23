/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 10:42:10 by abourbou          #+#    #+#             */
/*   Updated: 2020/12/23 20:43:21 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*start_pthread(void *vkit)
{
	t_phil_kit	*kit;


	kit = vkit;
	printf("thread number : %d starts\n", kit->my_number);
	printf("thread number : %d ends\n", kit->my_number);
	return (0);
}

void	destroy_arr_kit(t_phil_kit **tab_kit)
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

static t_phil_kit	**init_arr_kit(int number, unsigned long size_arr_kit, t_vars *global_var)
{
	t_phil_kit	**arr_kit;
	t_phil_kit	*kit;

	int	i;

	if (!(arr_kit = malloc(size_arr_kit)))
		return (0);
	memset(arr_kit, 0, size_arr_kit);
	i = 0;
	while (i < number)
	{
		if (!(kit = malloc(sizeof(t_phil_kit))))
		{	
			destroy_arr_kit(arr_kit);
			return (0);
		}
		arr_kit[i] = kit;
		(arr_kit[i])->vars = global_var;
		(arr_kit[i])->my_number = i;
		(arr_kit[i])->meal = 0;
		i++;
	}
	return (arr_kit);
}

int		launch_threads(t_vars *global_var, int number_phil)
{
	int			i;
	t_phil_kit	**arr_kit;
	pthread_t	*arr_thread;

	if (!(arr_kit = init_arr_kit(number_phil, global_var->size_arr_kit, global_var)))
		return (0);
	if (!(arr_thread = malloc(sizeof(pthread_t) * number_phil)))
	{
		destroy_arr_kit(arr_kit);
		return (0);
	}
	i = 0;
	while (i < number_phil)
	{
		pthread_create(&arr_thread[i], 0, start_pthread, arr_kit[i]);
		i++;
	}
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