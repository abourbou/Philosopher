/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 15:22:00 by abourbou          #+#    #+#             */
/*   Updated: 2021/01/19 20:30:28 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <pthread.h>
# include <semaphore.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <time.h>
# include <sys/time.h>
# include <sys/stat.h>

typedef struct	s_lsem
{
	sem_t	*s_fork;
	long	nbr_fork_available;
	sem_t	*s_speak;
	sem_t	*s_meal;
	sem_t	*s_eating;
}				t_lsem;

typedef struct	s_vars
{
	long	number_phil;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	max_meal;
	long	*compt_meal;
	long	*last_meal;
	int		stop;
	long	start_time;
}				t_vars;

typedef struct	s_kit
{
	t_vars		*vars;
	t_lsem		*l_sem;
	long		my_number;
	long		number_meal;
}				t_kit;

/*
** TOOLS
*/
long			ft_atoi(char *str);
long			get_time(void);
void			ft_putstr(char *str);
void			ft_putnbr(long nbr);
long			sleep_with_one_eye(t_vars *glob_var, long time_sleep);

/*
**LAUNCH THREADS
*/
int				launch_threads(t_vars *global_var, t_lsem *lst_sem,
												long number_phil);

/*
** MANAGEMENT_VAR
*/
int				init_glob(t_vars **glob_var, int argc, char **argv);
t_lsem			*init_sem(long number_phil);
void			destroy_glob(t_vars *glob_var, t_lsem *lsem);

/*
** CYCLE_THREAD
*/
void			*cycle_thread(void *vkit);
void			philo_speak(t_kit *kit, long start_time, long my_number,
													char *message);

/*
** MONITORING_THREADS
*/
void			*monitoring_threads(void *pkit);
#endif
