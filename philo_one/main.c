/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 12:09:26 by abourbou          #+#    #+#             */
/*   Updated: 2020/12/04 18:00:52 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo_one.h"

//!to erase
void	test_initialization(t_args args, t_mutex mutex)
{
	printf("nbr_philo : %d\n", args.nbr_philo);
	printf("times : %d %d %d\n", args.time_to_die, args.time_to_eat, args.time_to_sleep);
	printf("nbr_meal : %d\n", args.nbr_meal);
	printf("mutex speak : %p\n", &mutex.speak);
}

int		main(int argc, char **argv)
{
	t_args	args;
	t_mutex	mutex;

	if (!total_initialization(argc, argv, &args, &mutex))
		return (0);
	test_initialization(args, mutex);
	launch_thread(&args, &mutex);
	return (0);
}
