/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 15:09:01 by abourbou          #+#    #+#             */
/*   Updated: 2021/02/18 10:44:16 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int	verif_glob(t_vars *glob_var, int argc)
{
	if ((glob_var->number_phil <= 1 || glob_var->number_phil > 1000) ||
		glob_var->time_to_die <= 0 || glob_var->time_to_eat <= 0 ||
		glob_var->time_to_sleep <= 0 || (argc == 6 && glob_var->max_meal <= 0))
		return (-1);
	return (1);
}

t_lmutex	*init_mutex(long number_phil, int i)
{
	t_lmutex	*lstmutex;

	if (!(lstmutex = malloc(sizeof(t_lmutex))))
		return (0);
	memset((void *)lstmutex, 0, sizeof(lstmutex));
	if (!(lstmutex->m_fork = malloc(sizeof(pthread_mutex_t) * number_phil)))
	{
		if (lstmutex->m_fork)
			free(lstmutex->m_fork);
		free(lstmutex);
		return (0);
	}
	i = 0;
	while (i < number_phil)
	{
		pthread_mutex_init(&(lstmutex->m_fork[i]), NULL);
		i++;
	}
	pthread_mutex_init(&(lstmutex->m_speak), NULL);
	pthread_mutex_init(&(lstmutex->m_meal), NULL);
	return (lstmutex);
}

static void	init_fix_glob(t_vars *glob_var, int argc, char **argv)
{
	glob_var->number_phil = ft_atoi(argv[1]);
	glob_var->time_to_die = ft_atoi(argv[2]);
	glob_var->time_to_eat = ft_atoi(argv[3]);
	glob_var->time_to_sleep = ft_atoi(argv[4]);
	glob_var->max_meal = (argc == 6) ? ft_atoi(argv[5]) : -1;
	glob_var->compt_meal = 0;
	glob_var->stop = 0;
	glob_var->compt_meal = 0;
	glob_var->last_meal = 0;
	glob_var->start_time = 0;
}

/*
**	return 1 if it is a success
**	return 0 if malloc error
**	return -1 if bad variables
*/

int			init_glob(t_vars **pglob_var, int argc, char **argv)
{
	t_vars	*glob_var;

	if (!(glob_var = malloc(sizeof(t_vars))))
		return (0);
	*pglob_var = glob_var;
	init_fix_glob(glob_var, argc, argv);
	if (verif_glob(glob_var, argc) != 1)
		return (-1);
	if (!(glob_var->last_meal = malloc(sizeof(long) * glob_var->number_phil)))
		return (0);
	memset(glob_var->last_meal, 0, sizeof(long) * glob_var->number_phil);
	if (argc == 6)
	{
		if ((glob_var->compt_meal = malloc(sizeof(long) *
		(glob_var->number_phil + 1))) == 0)
			return (0);
		memset(glob_var->compt_meal, 0, glob_var->number_phil * sizeof(long));
		glob_var->compt_meal[glob_var->number_phil] = -1;
	}
	return (1);
}

void		destroy_glob(t_vars *glob_var, t_lmutex *lmutex, int i)
{
	if (!glob_var)
		return ;
	if (glob_var->compt_meal)
		free(glob_var->compt_meal);
	if (glob_var->last_meal)
		free(glob_var->last_meal);
	if (lmutex)
	{
		while (i < glob_var->number_phil)
		{
			if (pthread_mutex_destroy(&(lmutex->m_fork[i])))
				ft_putstr("impossible to destroy lock mutex in m_fork\n");
			i++;
		}
		if (pthread_mutex_destroy(&(lmutex->m_meal)))
			ft_putstr("impossible to destroy lock mutex in m_compt_meal\n");
		if (pthread_mutex_destroy(&(lmutex->m_speak)))
			ft_putstr("impossible to destroy lock mutex in m_speak\n");
		free((lmutex)->m_fork);
		free(lmutex);
	}
	free(glob_var);
}
