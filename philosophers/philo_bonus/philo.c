/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 08:40:28 by aait-lha          #+#    #+#             */
/*   Updated: 2024/10/01 03:01:13 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void	clean_up(t_philo_args *args)
{
	int	i;

	i = 0;
	while (i < args->nb_philo)
	{
		sem_close(&args->forks[i]);
		i++;
	}
	sem_close(&args->print);
	sem_close(&args->eat);
	sem_close(&args->dead_sem);
	sem_close(&args->life_sem);
	sem_close(&args->last_eat);
}

void	take_forks(t_philo *philo)
{
	t_philo_args	*args;

	args = philo->args;
	sem_wait(&args->forks[philo->right_fork]);
	sem_wait(&args->forks[philo->left_fork]);
	sem_wait(&args->print);
	printf("%ld %d has taken a fork\n", get_time() - philo->start_time, philo->id);
	sem_post(&args->print);
	sem_wait(&args->print);
	printf("%ld %d has taken a fork\n", get_time() - philo->start_time, philo->id);
	sem_post(&args->print);
}

void	eat(t_philo *philo)
{
	t_philo_args	*args;

	args = philo->args;
	sem_wait(&args->last_eat);
	philo->last_eat = get_time();
	sem_post(&args->last_eat);
	sem_wait(&args->print);
	printf("%ld %d is eating\n", get_time() - philo->start_time, philo->id);
	sem_post(&args->print);
	usleep(args->time_to_eat);
	philo->eat_count++;
	sem_post(&args->forks[philo->right_fork]);
	sem_post(&args->forks[philo->left_fork]);
}

void	philo_routine(t_philo *philo)
{
	t_philo_args	*args;

	args = philo->args;
	sem_wait(&args->last_eat);
	philo->last_eat = get_time();
	sem_post(&args->last_eat);
	while (1)
	{
		take_forks(philo);
		eat(philo);
		sem_wait(&args->print);
		printf("%ld %d is sleeping\n", get_time() - philo->start_time, philo->id);
		usleep(args->time_to_sleep);
		sem_post(&args->print);
	}
}

t_philo	*init_philos(t_philo_args *args)
{
	t_philo *philos;
	int		i;

	philos = malloc(sizeof(t_philo) * args->nb_philo);
	i = 0;
	while (i < args->nb_philo)
	{
		philos[i].id = i + 1;
		philos[i].args = args;
		philos[i].last_eat = get_time();
		philos[i].start_time = get_time();
		philos[i].eat_count = 0;
		philos[i].right_fork = i;
		philos[i].left_fork = (i + 1) % args->nb_philo;
		i++;
	}
	return (philos);
}

int	init(t_philo_args *args, t_philo **philos)
{
	int	i;

	args->forks = malloc(sizeof(sem_t) * args->nb_philo);
	args->print = 0;
	args->eat = 0;
	args->dead_sem = 0;
	args->life_sem = 0;
	args->last_eat = 0;
	i = 0;
	while (i < args->nb_philo)
	{
		sem_init(&args->forks[i], 0, 1);
		i++;
	}
	sem_init(&args->print, 0, 1);
	sem_init(&args->eat, 0, 1);
	sem_init(&args->dead_sem, 0, 1);
	sem_init(&args->life_sem, 0, 1);
	sem_init(&args->last_eat, 0, 1);
	*philos = init_philos(args);
	return (0);
}

int	main(int ac, char *av[])
{
	t_philo			*philos;
	t_philo_args	args;
	pid_t			pid;
	int				i;

	if (ac < 5 || ac > 6)
		return (write(2, "Error\n", 6));
	if (check_args(&args, av))
		return (write(2, "Error\n", 6));
	if (init(&args, &philos))
		return (write(2, "Error\n", 6));
	i = 0;
	while (i < args.nb_philo)
	{
		pid = fork();
		if (pid < 0)
			return (write(2, "Error\n", 6));
		if (pid == 0)
			philo_routine(&philos[i]);
		i++;
	}
	while (waitpid(-1, NULL, 0) > 0)
		;
	clean_up(&args);
	return (0);
}
