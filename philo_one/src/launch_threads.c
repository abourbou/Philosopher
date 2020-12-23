/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 10:42:10 by abourbou          #+#    #+#             */
/*   Updated: 2020/12/23 20:03:48 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*start_pthread(void *vkit)
{

}

void	destroy_tab_kit(t_phil_kit **tab_kit)
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

t_phil_kit		*init_tab_kit(int number, t_phil_kit **tab_kit, unsigned long size_tab_kit, t_vars *global_var)
{
	t_phil_kit	*kit;

	int	i;

	memset(tab_kit, 0, size_tab_kit); 
	i = 0;
	while (i < number)
	{
		if (!(kit = malloc(sizeof(t_phil_kit))))
		{	
			destroy_tab_kit(tab_kit);
			return (0);
		}
		tab_kit[i] = kit;
		(tab_kit[i])->vars = global_var;
		(tab_kit[i])->my_number = i;
		(tab_kit[i])->meal = 0;
		i++;
	}
	return (1);
}

int		launch_threads(t_vars *global_var)
{
	int			i;
	t_phil_kit	**tab_kit;

	if (!(tab_kit = malloc(global_var->size_tab_kit)))
		return (0);
	if (!init_tab_kit(global_var->number_phil, global_var->size_tab_kit))
		return (0);
	i = 0;
	while (i < global_var->number_phil)
	{
		pthread_create()
	}
	destroy_tab_kit(tab_kit);
	return (1);
}