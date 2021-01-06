/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 10:39:11 by abourbou          #+#    #+#             */
/*   Updated: 2020/08/20 10:39:11 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo_one.h"

void		ft_putstr(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	write(1, str, i);
}

long	ft_atoi(char *str)
{
	int		i;
	long	number;

	i = 0;
	number = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = number * 10;
		number += (long)(str[i] - '0');
		i++;
	}
	return (number);
}

static char	*reverse_str(char *str, unsigned long size)
{
	char	*rev_str;
	long	i;
	long	j;

	i = 0;
	j = 0;
	if (!(rev_str = malloc(sizeof(char) * size)))
		return (0);
	memset(rev_str, 0, sizeof(char) * size);
	while (str[j] && j < (long)size)
		j++;
	j--;
	while (j >= 0)
	{
		rev_str[i] = str[j];
		i++;
		j--;
	}
	return (rev_str);
}

char	*ft_itoa(long number)
{
	char			*str;
	char			*buffer;
	int				i;
	long			remainder;
	unsigned long	unumber;
	int				is_negat;

	if (!(buffer = malloc(21 * sizeof(char))))
		return (0);
	memset(buffer, 0, 21 * sizeof(char));
	i = 0;
	unumber = (number < 0) ? -number : number;
	is_negat = (number < 0) ? 1 : 0;
	while (unumber)
	{
		remainder = unumber % 10;
		unumber = unumber / 10;
		buffer[i] = (char)remainder + '0';
		i++;
	}
	buffer[i] = (is_negat) ? '-' : 0;
	str = reverse_str(buffer, 21 * sizeof(char));
	free(buffer);
	return (str);
}

long	get_time(long start_time)
{
	struct timeval	scurrent_time;
	long			current_time;

	gettimeofday(&scurrent_time, NULL);
	current_time = scurrent_time.tv_sec * 1000 + scurrent_time.tv_usec;
	return (current_time - start_time);
}
