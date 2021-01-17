/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 15:09:01 by abourbou          #+#    #+#             */
/*   Updated: 2021/01/17 20:12:39 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static int	verif_glob(t_vars *glob_var, int argc)
{
	if ((glob_var->number_phil <= 1 || glob_var->number_phil > 1000) ||
		glob_var->time_to_die <= 0 || glob_var->time_to_eat <= 0 ||
		glob_var->time_to_sleep <= 0 || (argc == 6 && glob_var->max_meal <= 0))
		return (-1);
	return (1);
}

t_lsem	*init_sem(long number_phil)
{
	t_lsem	*lstsem;

	if (!(lstsem = malloc(sizeof(t_lsem))))
	{
		ft_putstr("Malloc error\n");
		return (0);
	}
	sem_unlink("fork");
	sem_unlink("speak");
	sem_unlink("meal");
	lstsem->s_fork = sem_open("fork", O_CREAT, S_IRWXO, (int)number_phil);
	lstsem->nbr_fork_available = number_phil;
	lstsem->s_speak = sem_open("speak", O_CREAT, S_IRWXO, 1);
	lstsem->s_meal = sem_open("meal", O_CREAT, S_IRWXO, 1);
	if (lstsem->s_fork == SEM_FAILED || lstsem->s_meal == SEM_FAILED || lstsem->s_speak == SEM_FAILED)
	{
		ft_putstr("Sem_open error\n");
		ft_putstr(strerror(errno));
		free(lstsem);
		return (0);
	}
	return (lstsem);
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

void		destroy_glob(t_vars *glob_var, t_lsem *lsem)
{
	if (!glob_var)
		return ;
	if (glob_var->compt_meal)
		free(glob_var->compt_meal);
	if (glob_var->last_meal)
		free(glob_var->last_meal);
	if (lsem)
	{
		sem_unlink("fork");
		sem_unlink("speak");
		sem_unlink("meal");
		free(lsem);
	}
	free(glob_var);
}
