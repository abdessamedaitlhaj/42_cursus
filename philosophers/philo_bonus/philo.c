/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 08:40:28 by aait-lha          #+#    #+#             */
/*   Updated: 2024/09/26 22:03:35 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void	print(t_philo *philo, int id, char *str)
{
	long	now_time;
	pthread_mutex_lock(&philo->args->print);
	now_time = get_time() - philo->start_time;
	if (!philo->args->dead)
		printf("%ld %d %s\n", now_time, id, str);
	pthread_mutex_unlock(&philo->args->print);
}

int	take_fork(t_philo *philo)
{
	if (philo->args->nb_philo == 1)
	{  
		pthread_mutex_lock(&(philo->args->forks[philo->left_fork]));
		print(philo, philo->id, "has taken a fork");
		pthread_mutex_unlock(&(philo->args->forks[philo->left_fork]));
		return (1);
	}
	pthread_mutex_lock(&(philo->args->forks[philo->left_fork]));
	print(philo, philo->id, "has taken a fork"); 
	pthread_mutex_lock(&(philo->args->forks[philo->right_fork]));
	print(philo, philo->id, "has taken a fork");
	return (0);
} 

void	philo_eating(t_philo *philo)
{
	print(philo, philo->id, "is eating");
	pthread_mutex_lock(&philo->args->mutex_last_eat);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->args->mutex_last_eat);
	ft_usleep(philo->args->time_to_eat);
	pthread_mutex_lock(&philo->args->mutex_eat_count);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->args->mutex_eat_count);
	pthread_mutex_unlock(&(philo->args->forks[philo->left_fork]));
	pthread_mutex_unlock(&(philo->args->forks[philo->right_fork]));
}

void	*philo_routine(void *data)
{
	t_philo		*philo;

	philo = (t_philo *)data;
	if (philo->id % 2 == 0)
		ft_usleep(100);
	while (!philo->args->dead)
	{
		if (take_fork(philo))
			break ;
		philo_eating(philo);
		print(philo, philo->id, "is sleeping");
		ft_usleep(philo->args->time_to_sleep);
		print(philo, philo->id, "is thinking");
	}
	return (0);
}

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
	i = 0;
	while (i < args.nb_philo)
	{
		pthread_mutex_lock(&args.mutex_last_eat);
		philos[i].last_eat = get_time();
		pthread_mutex_unlock(&args.mutex_last_eat);
		philos[i].start_time = get_time();
		if (pthread_create(&(philos[i].thread), NULL, (void *)philo_routine, &philos[i]))
			return (1);
		i++;
	}
	i = 0;
	while (i < args.nb_philo)
	{
		if (pthread_join(philos[i].thread, NULL))
			return (write(2, "Error\n", 6));
		i++;
	}
	if (pthread_join(monitor, NULL))
		return (write(2, "Error\n", 6));
	clean_up(&args);
	return (0);
}
