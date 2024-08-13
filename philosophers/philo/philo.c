/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 08:40:28 by aait-lha          #+#    #+#             */
/*   Updated: 2024/08/13 22:33:54 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

// static int	is_empty(char *str)
// {
// 	while (*str)
// 	{
// 		if (!ft_isspace(*str))
// 			return (0);
// 		str++;
// 	}
// 	return (1);
// }

int	get_fork(t_philo *philo)
{
	if (philo->args-> == 1)
	{
		pthread_mutex_lock(&(philo->args->forks[philo->left_fork]));
		philo_printf(philo, philo->id, "has taken a fork");
		pthread_mutex_unlock(&(philo->args->forks[philo->left_fork]));
		return (1);
	}
	pthread_mutex_lock(&(philo->args->forks[philo->left_fork]));
	philo_printf(philo, philo->id, "has taken a fork");
	pthread_mutex_lock(&(philo->args->forks[philo->right_fork]));
	philo_printf(philo, philo->id, "has taken a fork");
	return (0);
}

void	*philo_routine(void *data)
{
	t_philo		*philo;

	philo = data;
	if (philo->id % 2 == 0)
		usleep(100);
	while (!checking(philo->args))
	{
		if (get_fork(philo))
			break ;
		if (checking(philo->args))
		{
			pthread_mutex_unlock(&(philo->args->forks[philo->left_fork]));
			pthread_mutex_unlock(&(philo->args->forks[philo->right_fork]));
			break ;
		}
		philo_eating(philo);
		if (checking(philo->args))
			break ;
		print(philo, philo->id, "is sleeping");
		ft_usleep(philo->args->time_to_sleep);
		if (checking(philo->args))
			break ;
		print(philo, philo->id, "is thinking");
	}
	return (0);
}

long	get_time(void)
{
	struct timeval	time;
	long			result;

	if (gettimeofday(&time, NULL))
		error();
	result = ((size_t)time.tv_sec * 1000) + ((size_t)time.tv_usec / 1000);
	return (result);
}

int	check_args(t_philo_args *args, char **av)
{
	args->nb_philo = ft_atoi(av[1], NULL);
	args->time_to_die = ft_atoi(av[2], NULL);
	args->time_to_eat = ft_atoi(av[3], NULL);
	args->time_to_sleep = ft_atoi(av[4], NULL);
	if (av[5])
		args->nb_must_eat = ft_atoi(av[5], NULL);
	else
		args->nb_must_eat = -1;
	if (args->nb_philo < 1 || args->time_to_die < 0 || args->time_to_eat < 0
		|| args->time_to_sleep < 0 || (av[5] && args->nb_must_eat <= 0))
		return (1);
	return (0);
}

t_philo	*init_philos(t_philo_args *args)
{
	t_philo		*philos;
	int			i;

	philos = malloc(sizeof(t_philo) * args->nb_philo);
	if (!philos)
		error();
	i = 0;
	while (i < args->nb_philo)
	{
		philos[i].id = i + 1;
		philos[i].right_fork = i;
		philos[i].left_fork = (i + 1) % args->nb_philo;
		philos[i].last_meal = 0;
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
		error();
	i = 0;
	while (i < nb_forks)
	{
		if (pthread_mutex_init(&forks[i], NULL))
			error();
		i++;
	}
	return (forks);
}

void	philo_routine(t_philo *philo)
{
	printf("philo %d\n", philo->id);
	if (philo->id % 2)
	{
		sleep(1);
	}
}

int	main(int ac, char *av[])
{
	t_philo			*philos;
	t_philo_args	args;

	if (ac < 5 || ac > 6)
		error();
	if (check_args(&args, av))
		error();
	philos = init_philos(&args);
	args.forks = init_forks(args.nb_philo);
	int i = 0;
	while (i < args.nb_philo)
	{
		if (pthread_create(&philos[i].thread, NULL, (void *)&philo_routine, &philos[i]))
			error();
		i++;
	}
	return (0);
}