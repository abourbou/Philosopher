/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 10:59:57 by abourbou          #+#    #+#             */
/*   Updated: 2020/07/28 10:59:57 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "headers/philo_one.h"

//return 1 if no error else return 0
int		verif_glob(t_vars *glob_var, int argc)
{
	if (glob_var->number_phil <= 0 || glob_var->time_to_die <= 0
		|| glob_var->time_to_eat <= 0 || glob_var->time_to_sleep <= 0
		|| (argc == 6 && glob_var->max_meal <= 0))
		return (-1);
	return (1);
}

int		init_mutex(t_vars *glob_var, int number_phil)
{
	t_lmutex	*lstmutex;
	int			i;

	lstmutex = &(glob_var->lmutex);
	if (!(lstmutex->m_fork = malloc(sizeof(pthread_mutex_t) * number_phil)))
		return (0);
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

int		init_glob(t_vars *glob_var, int argc, char **argv)
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

int		main(int argc, char **argv)
{
	int		return_value;
	t_vars	glob_var;

	if (argc < 5 || argc > 6)
	{
		ft_putstr("number of arguments incorrect\n");
		return (0);
	}
	printf("number of arguments correct\n");
	if ((return_value = init_glob(&glob_var, argc, argv)) <= 0)
	{
		if (return_value == 0)
			ft_putstr("Malloc error\n");
		else
			ft_putstr("Incorrect variable\n");
		return (0);
	}
	printf("initialization successfull\n");
	if (!launch_threads(&glob_var, glob_var.number_phil))
		ft_putstr("Malloc error\n");
	else
		printf("Successfull end of the threads, program finished\n");
	return (0);
}