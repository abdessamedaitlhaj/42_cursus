/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 22:23:02 by aait-lha          #+#    #+#             */
/*   Updated: 2024/09/28 10:31:54 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	last_eat(t_philo *philo)
{
	long	last;

	pthread_mutex_lock(&philo->args->mutex_last_eat);
	last = philo->last_eat;
	if (last == 0)
		last = get_time();
	pthread_mutex_unlock(&philo->args->mutex_last_eat);
	return (last);
}

int	philo_dead(t_philo *philos)
{
	long			now_time;
	int				i;
	int				nb_philo;
	t_philo_args	*args;

	nb_philo = philos[0].args->nb_philo;
	args = philos[0].args;
	i = 0;
	while (i < nb_philo)
	{
		now_time = get_time();
		if (now_time - last_eat(&philos[i]) > args->time_to_die)
		{
			print(&philos[i], philos[i].id, "died");
			args->dead = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

int	get_eat_count(t_philo philo)
{
	int	count;

	pthread_mutex_lock(&philo.args->mutex_eat_count);
	count = philo.eat_count;
	pthread_mutex_unlock(&philo.args->mutex_eat_count);
	return (count);
}

int	philos_eat(t_philo *philos)
{
	int				i;
	int				nb_philo;
	t_philo_args	*args;

	nb_philo = philos[0].args->nb_philo;
	args = philos[0].args;
	i = 0;
	while (i < nb_philo)
	{
		if (args->nb_must_eat != -1 && get_eat_count(philos[i]) >= args->nb_must_eat)
		{
			print(&philos[i], philos[i].id, "died");
			args->dead = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

void	*monitoring(void *data)
{
	t_philo	    *philos;
	t_philo_args	*args;

	philos = (t_philo *)data;
	args = philos[0].args;
	while (1)
	{
		if (philo_dead(philos) || philos_eat(philos))
			break ;
		ft_usleep(10);
	}
	return (0);
} 