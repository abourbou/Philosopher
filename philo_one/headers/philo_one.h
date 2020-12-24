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
	int				number_phil;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meal;
	int				*compt_meal;
	t_lmutex		lmutex;
	int				stop;
	unsigned long	size_arr_kit;
}				t_vars;

typedef struct	s_phil_kit
{
	t_vars	*vars;
	int		my_number;
	int		meal;
}				t_phil_kit;

// TOOLS
void		ft_putstr(char *str);
int			ft_atoi(char *str);

// LAUNCH THREADS

int		launch_threads(t_vars *global_var, int number_phil);
#endif