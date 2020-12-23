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

/*
**	return 1 if it is a success
**	return 0 if malloc error
**	return -1 if bad variables
*/

int		init_glob(t_vars *glob_var, int argc, char **argv)
{
	int i;

	glob_var->number_phil = ft_atoi(argv[1]);
	glob_var->time_to_die = ft_atoi(argv[2]);
	glob_var->time_to_eat = ft_atoi(argv[3]);
	glob_var->time_to_sleep = ft_atoi(argv[4]);
	glob_var->max_meal = (argc == 6) ? ft_atoi(argv[5]) : -1;
	glob_var->compt_meal = 0;
	if (argc == 6)
	{
		i = 0;
		if ((glob_var->compt_meal = malloc(sizeof(int) * 
		(glob_var->number_phil + 1))) == 0)
			return (0);
		while (i < glob_var->number_phil)
		{
			glob_var->compt_meal[i] = 0;
			i++;
		}
		glob_var->compt_meal[i] = -1;
	}
	glob_var->stop = 0;
	if (glob_var->number_phil > 0)
		glob_var->size_tab_kit = sizeof(t_phil_kit*) * (glob_var->number_phil + 1);
	return (verif_glob(glob_var, argc));
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
	 if (!launch_threads(&glob_var))
	 	ft_putstr("Malloc error\n");
	else
		printf("Successfull end of the threads, program fnished\n");
	return (0);
}