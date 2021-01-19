/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_forks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 14:46:12 by abourbou          #+#    #+#             */
/*   Updated: 2021/01/19 15:08:10 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	destroy_fork(pid_t *tab_pid, int max)
{
	int		i;

	i = 0;
	while (i < max)
	{
		if (tab_pid[i])
			kill(tab_pid[i], SIGINT);
		i++;
	}
}

void	find_fork(pid_t *tab_pid, int max, pid_t id)
{
	int	i;

	i = 0;
	while (i < max)
	{
		if (tab_pid[i] == id)
		{
			tab_pid[i] = 0;
			break ;
		}
		i++;
	}
}

int		wait_and_stop_forks(pid_t *tab_pid, long number_phil)
{
	int		i;
	int		status;
	pid_t	pid_ret;

	i = 0;
	while (i < number_phil)
	{
		pid_ret = waitpid(-1, &status, 0);
		find_fork(tab_pid, number_phil, pid_ret);
		if (status % 255 == 1)
		{
			destroy_fork(tab_pid, number_phil);
			break ;
		}
		i++;
	}
	free(tab_pid);
	return (0);
}

void	init_kit(t_kit *kit, t_vars *global_var, t_lsem *lst_sem)
{
	kit->vars = global_var;
	kit->l_sem = lst_sem;
	kit->vars->start_time = get_time();
	kit->number_meal = 0;
}

int		launch_forks(t_vars *global_var, t_lsem *lst_sem,
												long number_phil)
{
	int		i;
	pid_t	*tab_pid;
	t_kit	kit;

	if (!(tab_pid = malloc(sizeof(pid_t) * number_phil)))
		return (0);
	init_kit(&kit, global_var, lst_sem);
	i = 0;
	while (i < number_phil)
	{
		if ((tab_pid[i] = fork()) < 0)
		{
			destroy_fork(tab_pid, i);
			ft_putstr("Error creation fork\n");
			return (-1);
		}
		if (tab_pid[i] == 0)
		{
			kit.my_number = i;
			cycle_fork(&kit);
			exit(2);
		}
		i++;
	}
	return (wait_and_stop_forks(tab_pid, number_phil));
}
