/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 10:59:57 by abourbou          #+#    #+#             */
/*   Updated: 2021/01/18 22:51:27 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "headers/philo_three.h"

static int	init_main_glob(t_vars **glob_var, int argc, char **argv)
{
	int		return_value;

	if ((return_value = init_glob(glob_var, argc, argv)) <= 0)
	{
		if (return_value == 0)
			ft_putstr("Malloc error in init_glob\n");
		else
			ft_putstr("Incorrect variable\n");
		destroy_glob(*glob_var, 0);
		return (1);
	}
	return (0);
}

int			main(int argc, char **argv)
{
	t_vars	*glob_var;
	t_lsem	*lst_sem;
	int		return_value;

	glob_var = 0;
	if (argc < 5 || argc > 6)
	{
		ft_putstr("number of arguments incorrect\n");
		return (0);
	}
	if (init_main_glob(&glob_var, argc, argv))
		return (0);
	if (!(lst_sem = init_sem(glob_var->number_phil)))
	{
		destroy_glob(glob_var, 0);
		return (0);
	}
	return_value = launch_forks(glob_var, lst_sem, glob_var->number_phil);
	destroy_glob(glob_var, lst_sem);
	return (return_value);
}
