/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 15:22:10 by abourbou          #+#    #+#             */
/*   Updated: 2021/01/02 22:25:57 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*start_pthread(void *vkit)
{
	t_phil_kit	*kit;

	kit = vkit;
	pthread_mutex_lock(&(kit->vars->lmutex->m_meal));
	kit->vars->last_meal[kit->my_number] = get_time(0);
	pthread_mutex_unlock(&(kit->vars->lmutex->m_meal));

//! to erase
	pthread_mutex_lock(&(kit->vars->lmutex->m_speak));
	printf("thread number : %d starts\n", kit->my_number);
	printf("my time is : %ld\n", get_time(kit->vars->start_time[kit->my_number]));
	pthread_mutex_unlock(&(kit->vars->lmutex->m_speak));
//!
	


	return (0);
}
