/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 22:14:16 by aait-lha          #+#    #+#             */
/*   Updated: 2024/09/25 22:15:18 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*init_philos(t_philo_args *args)
{
	t_philo		*philos;
	int			i;

	philos = malloc(sizeof(t_philo) * args->nb_philo);
	if (!philos)
	{
		write(2, "Error\n", 6);
		return (NULL);
	}
	i = 0;
	while (i < args->nb_philo)
	{
		philos[i].id = i + 1;
		philos[i].right_fork = i;
		philos[i].left_fork = (i + 1) % args->nb_philo;
		philos[i].last_eat = 0;
		philos[i].eat_count = 0;
		philos[i].thread = 0;
		philos[i].args = args;
		i++;
	}
	return (philos);
}

pthread_mutex_t	*init_forks(int nb_forks)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t) * nb_forks);
	if (!forks)
	{
		write(2, "Error\n", 6);
		return (NULL);
	}
	i = 0;
	while (i < nb_forks)
	{
		if (pthread_mutex_init(&forks[i], NULL))
		{
			write (2, "Error\n", 6);
			return (NULL);
		}
		i++;
	}
	return (forks);
}

int	init_data(t_philo_args *args, t_philo **philos)
{
	pthread_mutex_init(&args->print, NULL);
	pthread_mutex_init(&args->mutex_last_eat, NULL);
	pthread_mutex_init(&args->mutex_eat_count, NULL);
	*philos = init_philos(args);
	args->forks = init_forks(args->nb_philo);
	if (!*philos || !args->forks)
		return (1);
	return (0);
}