/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 08:40:28 by aait-lha          #+#    #+#             */
/*   Updated: 2024/10/03 19:47:34 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"


void	print(t_philo *philo, int id, char *str)
{
	long	now_time;
	now_time = get_time() - philo->start_time;
	printf("%ld %d %s\n", now_time, id, str);
}

int	take_fork(t_philo *philo)
{
	if (philo->args->nb_philo == 1)
	{  
		sem_wait(philo->args->fork);
		print(philo, philo->id, "has taken a fork");
		sem_post(philo->args->fork);
		return (1);
	}
	sem_wait(philo->args->fork);
	print(philo, philo->id, "has taken a fork"); 
	sem_wait(philo->args->fork);
	print(philo, philo->id, "has taken a fork");
	return (0);
} 

void	philo_eating(t_philo *philo)
{
	print(philo, philo->id, "is eating");
	philo->last_eat = get_time();
	ft_usleep(philo->args->time_to_eat);
	philo->eat_count++;
	sem_post(philo->args->fork);
	sem_post(philo->args->fork);
}

void	*monitor(void *data)
{
	t_philo		*philo;

	philo = (t_philo *)data;
	while (1)
	{
		if (philo->args->nb_meals != -1 && philo->eat_count >= philo->args->nb_meals || philo->args->time_to_die < get_time() - philo->last_eat)
			exit(1);
	}
}

void	*philo_routine(void *data)
{
	t_philo		*philo;

	philo = (t_philo *)data;
	if (philo->id % 2 == 0)
		ft_usleep(100);
	if (pthread_create(&philo->thread, NULL, (void *)monitor, philo))
		return (NULL);
	while (1)
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

int	check_args(t_philo_args *args, char **av)
{
	args->nb_philo = ft_atoi(av[1], NULL);
	args->time_to_die = ft_atoi(av[2], NULL);
	args->time_to_eat = ft_atoi(av[3], NULL);
	args->time_to_sleep = ft_atoi(av[4], NULL);
	if (av[5])
		args->nb_meals = ft_atoi(av[5], NULL);
	else
		args->nb_meals = -1;
	if (args->nb_philo < 1 || args->time_to_die < 0 || args->time_to_eat < 0
		|| args->time_to_sleep < 0 || (av[5] && args->nb_meals <= 0))
		return (1);
	if (args->time_to_die < 60 || args->time_to_eat < 60 || args->time_to_sleep < 60 || args->nb_philo > 200)
		return (1);
	args->dead = 0;
	args->start = 0;
	return (0);
}


t_philo	*init_philos(t_philo_args *args)
{
	t_philo		*philos;
	int			i;

	philos = malloc(sizeof(t_philo) * args->nb_philo);
	if (!philos)
		return (NULL);
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

int	init_data(t_philo_args *args)
{
	if (sem_unlink("fork"))
		return (1);
	sem_unlink("print");
		return (1);
	sem_unlink("die");
		return (1);
	args->fork = sem_open("fork", O_CREAT, 0644, args->nb_philo);
	if (args->fork == SEM_FAILED)
		return (1);
	args->print = sem_open("print", O_CREAT, 0644, 1);
	if (args->print == SEM_FAILED)
		return (1);
	args->die = sem_open("die", O_CREAT, 0644, 1);
	if (args->die == SEM_FAILED)
		return (1);
	if (!init_philos(args))
		return (1);
	return (0);
}

int	clean_up(t_philo_args *args)
{
	if (sem_close(args->fork))
		return (1);
	if (sem_close(args->print))
		return (1);
	if (sem_close(args->die))
		return (1);
	if (sem_unlink("fork"))
		return (1);
	if (sem_unlink("print"))
		return (1);
	if (sem_unlink("die"))
		return (1);
	return (0);
}

int	main(int ac, char *av[])
{
	pthread_t		monitor;
	t_philo			*philos;
	t_philo_args	args;
	int				i;
	pid_t			*pids;
	int				status;

	if (ac < 5 || ac > 6)
		return (write(2, "Error\n", 6));
	if (check_args(&args, av))
		return (write(2, "Error\n", 6));
	if (init_data(&args))
		return (write(2, "Error\n", 6));
	pids = malloc(sizeof(pid_t) * args.nb_philo);
	i = 0;
	while (i < args.nb_philo)
	{
		philos[i].start_time = get_time();
		philos[i].last_eat = get_time();
		pids[i] = fork();
		if (pids[i] == -1)
			return (write(2, "Error\n", 6));
		if (pids[i] == 0)
			philo_routine(&philos[i]);
		i++;
	}
	waitpid(-1, &status, 0);
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 1)
			kill(0, SIGKILL);
	}
	if (clean_up(&args))
		return (write(2, "Error\n", 6));
	return (0);
}
