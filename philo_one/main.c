/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 12:09:26 by abourbou          #+#    #+#             */
/*   Updated: 2020/12/04 17:03:21 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo_one.h"

int		main(int argc, char **argv)
{
	t_args	args;
	t_mutex	mutex;

	total_initialization(argc, argv, &args, &mutex);
	//launch_thread(&args, &mutex);
	return (0);
}