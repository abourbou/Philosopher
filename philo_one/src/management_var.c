/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 15:09:01 by abourbou          #+#    #+#             */
/*   Updated: 2020/12/24 15:25:38 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

//return 1 if no error else return 0
static int		verif_glob(t_vars *glob_var, int argc)
{
	if (glob_var->number_phil <= 0 || glob_var->time_to_die <= 0
		|| glob_var->time_to_eat <= 0 || glob_var->time_to_sleep <= 0
		|| (argc == 6 && glob_var->max_meal <= 0))
		return (-1);
	return (1);
}

static int		init_mutex(t_vars *glob_var, int number_phil)
{
	t_lmutex	*lstmutex;
	int			i;

	if (!(glob_var->lmutex = malloc(sizeof(t_lmutex))))
		return (0);
	lstmutex = glob_var->lmutex;
	if (!(lstmutex->m_fork = malloc(sizeof(pthread_mutex_t) * number_phil)))
	{
		free(lstmutex);
		return (0);
	}
	i = 0;
	while (i < number_phil)
	{
		pthread_mutex_init(&(lstmutex->m_fork[i]), NULL);
		i++;
	}
	return (1);	
}

/*
**	return 1 if it is a success
**	return 0 if malloc error
**	return -1 if bad variables
*/

int				init_glob(t_vars *glob_var, int argc, char **argv)
{
	glob_var->number_phil = ft_atoi(argv[1]);
	glob_var->time_to_die = ft_atoi(argv[2]);
	glob_var->time_to_eat = ft_atoi(argv[3]);
	glob_var->time_to_sleep = ft_atoi(argv[4]);
	glob_var->max_meal = (argc == 6) ? ft_atoi(argv[5]) : -1;
	glob_var->compt_meal = 0;
	if (verif_glob(glob_var, argc) != 1)
		return (-1);
	if (argc == 6)
	{
		if ((glob_var->compt_meal = malloc(sizeof(int) * 
		(glob_var->number_phil + 1))) == 0)
			return (0);
		memset(glob_var->compt_meal, 0, glob_var->number_phil * sizeof(int));
		glob_var->compt_meal[glob_var->number_phil] = -1;
	}
	glob_var->stop = 0;
	glob_var->size_arr_kit = sizeof(t_phil_kit*) * (glob_var->number_phil + 1);
	if (!(init_mutex(glob_var, glob_var->number_phil)))
		return (0);
	return (1);
}

void		destroy_glob(t_vars *glob_var)
{
	if (glob_var->compt_meal)
		free(glob_var->compt_meal);
	free((glob_var->lmutex)->m_fork);
	free(glob_var->lmutex);
}
