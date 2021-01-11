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
	pthread_mutex_t	*m_fork;
	pthread_mutex_t	m_speak;
	pthread_mutex_t	m_meal;
}				t_lmutex;

typedef struct	s_vars
{
	long			number_phil;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			max_meal;
	long			*compt_meal;
	long			*last_meal;
	long			*start_time;
	int				stop;
}				t_vars;

typedef struct	s_kit
{
	t_vars		*vars;
	t_lmutex	*lmutex;
	int			my_number;
	int			number_meal;
}				t_kit;

// TOOLS
void		ft_putstr(char *str);
long		ft_atoi(char *str);
long		get_time(void);
char		*ft_itoa(long number);

// LAUNCH THREADS
int			launch_threads(t_vars *global_var, t_lmutex *lst_mutex, int number_phil);

// MANAGEMENT_VAR
int			init_glob(t_vars **glob_var, int argc, char **argv);
t_lmutex	*init_mutex(int number_phil);
void		destroy_glob(t_vars *glob_var, t_lmutex *lmutex);


// CYCLE_THREAD
void		*start_pthread(void *vkit);

// MONITORING_THREADS
void		*monitoring_threads(void *pglob_var);

#endif