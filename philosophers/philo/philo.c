/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 08:40:28 by aait-lha          #+#    #+#             */
/*   Updated: 2024/10/04 19:10:26 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_up(t_philo_args *args)
{
	int	i;

	i = 0;
	while (i < args->nb_philo)
	{
		pthread_mutex_destroy(&(args->forks[i]));
		i++;
	}
	pthread_mutex_destroy(&args->print);
	pthread_mutex_destroy(&args->mutex_last_eat);
	pthread_mutex_destroy(&args->mutex_eat_count);
	pthread_mutex_destroy(&args->mutex_dead);
}

int	join_threads(t_philo *philos, pthread_t *monitor, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		if (pthread_join(philos[i].thread, NULL))
			return (1);
		i++;
	}
	if (pthread_join(*monitor, NULL))
		return (1);
	return (0);
}

int	create_threads(t_philo *philos, t_philo_args *args)
{
	int	i;

	i = 0;
	while (i < args->nb_philo)
	{
		pthread_mutex_lock(&args->mutex_last_eat);
		philos[i].last_eat = get_time();
		pthread_mutex_unlock(&args->mutex_last_eat);
		philos[i].start_time = get_time();
		if (pthread_create(&(philos[i].thread), NULL, \
		(void *)philo_routine, &philos[i]))
			return (1);
		i++;
	}
	return (0);
}

int	main(int ac, char *av[])
{
	pthread_t		monitor;
	t_philo			*philos;
	t_philo_args	args;
	int				i;

	if (ac < 5 || ac > 6)
		return (write(2, "Error\n", 6));
	if (check_args(&args, av))
		return (write(2, "Error\n", 6));
	if (init_data(&args, &philos))
		return (write(2, "Error\n", 6));
	if (pthread_create(&monitor, NULL, (void *)monitoring, philos))
		return (write(2, "Error\n", 6));
	if (create_threads(philos, &args))
		return (write(2, "Error\n", 6));
	if (join_threads(philos, &monitor, args.nb_philo))
		return (write(2, "Error\n", 6));
	clean_up(&args);
	return (0);
}
