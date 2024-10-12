/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 09:00:51 by aait-lha          #+#    #+#             */
/*   Updated: 2024/10/12 01:08:10 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	get_time(void)
{
	struct timeval	time;
	long result;

	if (gettimeofday(&time, NULL))
		return (write(2, "Error\n", 6));
	result = ((size_t)time.tv_sec * 1000) + ((size_t)time.tv_usec / 1000);
	return (result);
}

void ft_usleep(long time)
{
    long long start;
    long long now;

    start = get_time();
    while (1)
    {
        now = get_time();
        if (now - start >= time)
            break;
        usleep(500);
    }
}