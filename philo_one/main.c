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


int		main(int argc, char **argv)
{
	int			return_value;
	t_vars		*glob_var;
	t_lmutex	*lst_mutex;

	glob_var = 0;
	if (argc < 5 || argc > 6)
	{
		ft_putstr("number of arguments incorrect\n");
		return (0);
	}
	if ((return_value = init_glob(&glob_var, argc, argv)) <= 0)
	{
		if (return_value == 0)
			ft_putstr("Malloc error in init_glob\n");
		else
			ft_putstr("Incorrect variable\n");
		destroy_glob(glob_var, 0); 
		return (0);
	}
	if (!(lst_mutex = init_mutex(glob_var->number_phil)))
	{
		ft_putstr("Malloc error in init_mutex\n");
		destroy_glob(glob_var, 0);
		return (0);
	}
	printf("initialization successfull\n");
	if (!launch_threads(glob_var, lst_mutex, glob_var->number_phil))
		ft_putstr("Malloc error\n");
	else
		printf("Successfull end of the threads, program finished\n");
	destroy_glob(glob_var, lst_mutex);
	return (0);
}