/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 08:40:28 by aait-lha          #+#    #+#             */
/*   Updated: 2024/09/08 18:11:58 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void	print(t_philo *philo, int id, char *str)
{
	long	now_time;
	pthread_mutex_lock(&philo->print);
	now_time = get_time() - philo->start_time;
	printf("%ld %d %s\n", now_time, id, str);
	pthread_mutex_unlock(&philo->print);
}

void	change_monitor(t_philo_args *args)
{
	pthread_mutex_lock(&args->mutex_monitor);
	args->monitor = 1;
	pthread_mutex_unlock(&args->mutex_monitor);
}

long	last_eat(t_philo *philo)
{
	long	last;
	pthread_mutex_lock(&philo->mutex_last_eat);
	last = philo->last_eat;
	pthread_mutex_unlock(&philo->mutex_last_eat);
	return (last);
}

int	checking(t_philo_args *arg)
{
	pthread_mutex_lock(&arg->mutex_monitor);
	if (arg->monitor == 1)
	{
		pthread_mutex_unlock(&arg->mutex_monitor) ;
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&arg->mutex_monitor);
		return (0);
	}
}

int	get_fork(t_philo *philo)
{
	// if (philo->args->nb_philo == 1)
	// {  
	// 	pthread_mutex_lock(&(philo->args->forks[philo->left_fork]));
	// 	print(philo, philo->id, "has taken a fork");
	// 	pthread_mutex_unlock(&(philo->args->forks[philo->left_fork]));
	// 	return (1);
	// }
	pthread_mutex_lock(&(philo->args->forks[philo->left_fork]));
	print(philo, philo->id, "has taken a fork"); 
	pthread_mutex_lock(&(philo->args->forks[philo->right_fork]));
	print(philo, philo->id, "has taken a fork");
	return (0);
} 

void	philo_eating(t_philo *philo)
{
	print(philo, philo->id, "is eating");
	pthread_mutex_lock(&philo->mutex_last_eat);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->mutex_last_eat);
	ft_usleep(philo->args->time_to_eat);
	pthread_mutex_lock(&philo->mutex_eat_count);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->mutex_eat_count);
	pthread_mutex_unlock(&(philo->args->forks[philo->left_fork]));
	pthread_mutex_unlock(&(philo->args->forks[philo->right_fork]));
}

void	*philo_routine(void *data)
{
	t_philo		*philo;

	philo = (t_philo *)data;
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

int	philo_dead(t_philo *philo)
{
	long	now_time;

	now_time = get_time();
	if ((now_time - last_eat(philo)) >= philo->args->time_to_die)
	{
		print(philo, philo->id, "died");
		return (1);
	}
	return (0);
}

void	cleaning(t_philo_args *args, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < args->nb_philo)
	{
		pthread_mutex_destroy(&philos[i].print);
		pthread_mutex_destroy(&philos[i].mutex_last_eat);
		pthread_mutex_destroy(&args->forks[i]);
		i++;
	}
	free(args->forks);
	free(philos);
}
void	*monitoring(void *data)
{
	t_philo		*philos;

	philos = (t_philo *)data;
	while (1)
	{
		if (philo_dead(philos))
		{
			change_monitor(philos[0].args);
			return (0);
		}
	}
	return (0);
}

int	main(int ac, char *av[])
{
	t_philo			*philos;
	t_philo_args	args;
	pthread_t		monitor;
	int				i;

	if (ac < 5 || ac > 6)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	if (check_args(&args, av))
	{
		write(2, "Error\n", 6);
		return (1);
	}
	philos = init_philos(&args);
	args.forks = init_forks(args.nb_philo);
	if (!args.forks)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	if (pthread_create(&monitor, NULL, (void *)monitoring, &args))
	{
		write(2, "Error\n", 6);
		return (1);
	}
	i = 0;
	while (i < args.nb_philo)
	{
		philos[i].start_time = get_time();
		if (pthread_create(&(philos[i].thread), NULL, (void *)philo_routine, &philos[i]))
			return (1);
		i++;
	}
	if (pthread_join(monitor, NULL))
	{
		write(2, "Error\n", 6);
		return (1);
	}
	i = 0;
	while (i < args.nb_philo)
	{
		if (pthread_join(philos[i].thread, NULL))
		{
			write(2, "Error\n", 6);
			return (1);
		}
		i++;
	}
	cleaning(&args, philos);
	return (0);
}