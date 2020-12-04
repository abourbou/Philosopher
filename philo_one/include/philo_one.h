/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 12:22:41 by abourbou          #+#    #+#             */
/*   Updated: 2020/12/04 15:49:14 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct	s_args
{
	int		nbr_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		nbr_meal;
	int		*meals;
}				t_args;

typedef struct s_mutex
{
	pthread_mutex_t	*fork;
	pthread_mutex_t	speak;
}				t_mutex;


typedef struct	s_kit
{
	int		serial_number;
	t_args	args;
	t_mutex	mutex;
}				t_kit;

//TOOLS_C
void	ft_putstr(char *str);
int		ft_atoi(char *str);

//INIT_C
int		total_initialization(int argc, char **argv, t_args *args, t_mutex *mutex);
#endif