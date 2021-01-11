/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 15:22:10 by abourbou          #+#    #+#             */
/*   Updated: 2021/01/11 11:52:20 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*start_pthread(void *vkit)
{
	t_kit	*kit;

	kit = vkit;
	pthread_mutex_lock(&(kit->lmutex->m_meal));
	kit->vars->last_meal[kit->my_number] = get_time();
	pthread_mutex_unlock(&(kit->lmutex->m_meal));

//! to erase
	pthread_mutex_lock(&(kit->lmutex->m_speak));
	printf("thread number : %d starts\n", kit->my_number);
	printf("last meal : %ld\n", kit->vars->last_meal[kit->my_number]);
	printf("my time is : %ld\n", get_time());
	pthread_mutex_unlock(&(kit->lmutex->m_speak));
//!
	
	return (0);
}
