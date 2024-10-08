/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 22:23:02 by aait-lha          #+#    #+#             */
/*   Updated: 2024/10/08 18:26:53 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	last_eat(t_philo *philo)
{
	long	last;

	pthread_mutex_lock(&philo->mutex_last_eat);
	last = philo->last_eat;
	pthread_mutex_unlock(&philo->mutex_last_eat);
	return (last);
}

int	get_flag(t_philo_args *args)
{
	int	flag;

	pthread_mutex_lock(&args->mutex_flag);
	flag = args->flag;
	pthread_mutex_unlock(&args->mutex_flag);
	return (flag);
}

void	*monitoring(void *data)
{
	t_philo			*philos;
	t_philo_args	*args;
	long			now_time;
	int				i;
	int				meals;

	philos = (t_philo *)data;
	args = philos[0].args;
	while (!get_flag(args))
		ft_usleep(10);
	while (1)
	{
		meals = args->meals;
		if (meals != -1)
		{
			i = 0;
			while (i < args->nb_philo)
			{
				if (get_eat_count(&philos[i]) >= meals)
					meals--;
				i++;
			}
			if (meals == 0)
				return (NULL);
		}
		i = 0;
		while (i < args->nb_philo)
		{
			now_time = get_time();
			if (now_time - last_eat(&philos[i]) >= args->die_time)
			{
				print(&philos[i], philos[i].id, "died");
				pthread_mutex_lock(&args->mutex_dead);
				args->dead = 1;
				pthread_mutex_unlock(&args->mutex_dead);
				return (NULL);
			}
			i++;
		}
	}
}
