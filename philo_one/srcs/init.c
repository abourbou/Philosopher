/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 14:50:54 by abourbou          #+#    #+#             */
/*   Updated: 2020/12/04 15:49:43 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

/*
**	check the validity of the args
**	valid args   : 1
**	invalid args : 0
*/
int		check_args(t_args args)
{
	if (!args.nbr_meal || !args.nbr_philo || !args.time_to_die
	|| !args.time_to_eat || !args.time_to_sleep)
		return (0);
	return (1);
}

/*
**	fill the arguments with argv
*/
void	fill_args(int argc, char **argv, t_args *args)
{
	args->nbr_philo = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	args->nbr_meal = (argc == 6) ? ft_atoi(argv[5]) : -1;
}

/*
** init all mutex with pthread_mutex_init, return 1 if success and 0 if failed
*/
int		init_mutex(t_mutex *mutex, int nbr_philo)
{
	int	i;

	i = 0;
	while (i < nbr_philo)
	{
		if (pthread_mutex_init(&(mutex->fork[i]), NULL))
			return (0);
		i++;
	}
	if (pthread_mutex_init(&(mutex->speak), NULL))
		return (0);
	return (1);
}

/*
** initialization of all variables of the program
** return 1 if success or 0 if error
*/

int		total_initialization(int argc, char **argv, t_args *args, t_mutex *mutex)
{
	if (argc < 5 || argc > 6)
	{
		ft_putstr("put the right number of arguments\n");
		return (0);
	}
	fill_args(argc, argv, args);
	if (!check_args(*args))
	{
		ft_putstr("put valids arguments\n");
		return (0);
	}
	if (!(mutex->fork = malloc(sizeof(pthread_mutex_t) * args->nbr_philo)))
	{
		ft_putstr("error malloc\n");
		return (0);
	}
	if (!init_mutex(mutex, args->nbr_philo))
	{
		ft_putstr("error init mutex\n");
		return (0);
	}
	return (1);
}