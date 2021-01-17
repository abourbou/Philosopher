/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 10:42:10 by abourbou          #+#    #+#             */
/*   Updated: 2021/01/17 15:39:42 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void			destroy_arr_kit(t_kit **tab_kit)
{
	int	i;

	i = 0;
	while (tab_kit[i])
	{
		free(tab_kit[i]);
		i++;
	}
	free(tab_kit);
}

static t_kit	**init_arr_kit(int number_phil, t_vars *global_var,
												t_lsem *lst_sem)
{
	t_kit	**arr_kit;
	t_kit	*kit;
	int		i;

	if (!(arr_kit = malloc((global_var->number_phil + 2) * sizeof(t_kit))))
		return (0);
	memset(arr_kit, 0, (global_var->number_phil + 2) * sizeof(t_kit));
	i = 0;
	while (i < number_phil + 1)
	{
		if (!(kit = malloc(sizeof(t_kit))))
		{
			destroy_arr_kit(arr_kit);
			return (0);
		}
		arr_kit[i] = kit;
		kit->vars = global_var;
		kit->l_sem = lst_sem;
		kit->my_number = i;
		kit->number_meal = 0;
		i++;
	}
	return (arr_kit);
}

static void		create_threads(t_kit **arr_kit, pthread_t *arr_thread,
													long number_phil)
{
	int i;

	pthread_create(&arr_thread[number_phil], 0, monitoring_threads,
												arr_kit[number_phil]);
	i = 0;
	while (i < number_phil)
	{
		pthread_create(&arr_thread[i], 0, cycle_thread, arr_kit[i]);
		i += 2;
	}
	usleep(1000);
	i = 1;
	while (i < number_phil)
	{
		pthread_create(&arr_thread[i], 0, cycle_thread, arr_kit[i]);
		i += 2;
	}
}

int				launch_threads(t_vars *global_var, t_lsem *lst_sem,
												long number_phil)
{
	int			i;
	t_kit		**arr_kit;
	pthread_t	*arr_thread;

	if (!(arr_kit = init_arr_kit(number_phil, global_var, lst_sem)))
		return (0);
	if (!(arr_thread = malloc(sizeof(pthread_t) * (number_phil + 1))))
	{
		destroy_arr_kit(arr_kit);
		return (0);
	}
	global_var->start_time = get_time();
	create_threads(arr_kit, arr_thread, number_phil);
	pthread_join(arr_thread[number_phil], 0);
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
