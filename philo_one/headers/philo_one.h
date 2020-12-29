/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 10:57:19 by abourbou          #+#    #+#             */
/*   Updated: 2020/07/28 10:57:19 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

//! a supprimer
#include <stdio.h>
//

// compt_meal est un tableau qui compte 
// le nombre de repas de chaque philosophe

typedef struct	s_lmutex
{
	pthread_mutex_t		*m_fork;
	pthread_mutex_t		m_speak;
	pthread_mutex_t		m_compt_meal;
}				t_lmutex;

typedef struct	s_vars
{
	long			number_phil;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			max_meal;
	long			*compt_meal;
	t_lmutex		*lmutex;
	int				stop;
	unsigned long	size_arr_kit;
	long			start_time;
}				t_vars;

typedef struct	s_phil_kit
{
	t_vars	*vars;
	int		my_number;
	int		meal;
}				t_phil_kit;

// TOOLS
void	ft_putstr(char *str);
long	ft_atoi(char *str);
long	get_time(long start_time);

// LAUNCH THREADS
int		launch_threads(t_vars *global_var, int number_phil);

// MANAGEMENT_VAR
int		init_glob(t_vars *glob_var, int argc, char **argv);
void	destroy_glob(t_vars *glob_var);

// CYCLE_THREAD
void	*start_pthread(void *vkit);

#endif