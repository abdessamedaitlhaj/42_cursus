/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 08:40:28 by aait-lha          #+#    #+#             */
/*   Updated: 2024/10/12 01:05:47 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo_bonus.h"


void	print(t_philo *philo, int id, char *str)
{
	long	now_time;

	sem_wait(philo->args->print);
	now_time = get_time();
	printf("%ld %d %s\n", now_time - philo->start_time, id, str);
	sem_post(philo->args->print);
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
	sem_wait(philo->last_eat_sem);
	philo->last_eat = get_time();
	sem_post(philo->last_eat_sem);
	ft_usleep(philo->args->eat_time);
	sem_wait(philo->eat_count_sem);
	philo->eat_count++;
	sem_post(philo->eat_count_sem);
	sem_post(philo->args->fork);
	sem_post(philo->args->fork);
}

long	get_last_eat(t_philo *philo)
{
	long	last_eat;

	sem_wait(philo->last_eat_sem);
	last_eat = philo->last_eat;
	sem_post(philo->last_eat_sem);
	return (last_eat);
}

int	get_eat_count(t_philo *philo)
{
	int	eat_count;

	sem_wait(philo->eat_count_sem);
	eat_count = philo->eat_count;
	sem_post(philo->eat_count_sem);
	return (eat_count);
}

void	*monitor(void *data)
{
	t_philo		*philo;
	long		now_time;
	int			meals;

	philo = (t_philo *)data;
	meals = philo->args->meals;
	ft_usleep(philo->args->eat_time);
	while (1)
	{
		now_time = get_time();
		if (now_time - get_last_eat(philo) >= philo->args->die_time)
		{
			sem_wait(philo->args->print);
			printf("%ld %d died\n", get_time() - philo->start_time, philo->id);
			exit(1);
		}
		ft_usleep(1000);
	}
}

void	init_local_sem(t_philo *philo)
{
	sem_unlink("last_eat");
	sem_unlink("eat_count");
	philo->last_eat_sem = sem_open("last_eat", O_CREAT, 0644, 1);
	philo->eat_count_sem = sem_open("eat_count", O_CREAT, 0644, 1);
}

void	clean_local_sem(t_philo *philo)
{
	sem_close(philo->last_eat_sem);
	sem_close(philo->eat_count_sem);
	sem_unlink("last_eat");
	sem_unlink("eat_count");
}

void	set_start_time(t_philo *philo, int *counter)
{
	sem_wait(philo->args->print);
	if (*counter == 0)
	{
		philo->args->start_time = get_time();
		*counter = 1;
	}
	sem_post(philo->args->print);
}
void	*philo_routine(void *data)
{
	t_philo		*philo;
	sem_t		*last_eat_sem;
	sem_t		*eat_count_sem;

	philo = (t_philo *)data;
	sem_wait(philo->args->s);
	init_local_sem(philo);
	set_start_time(philo, &philo->args->counter);
	sem_wait(philo->last_eat_sem);
	philo->last_eat = philo->args->start_time;
	sem_post(philo->last_eat_sem);
	philo->start_time = philo->args->start_time;
	if (philo->id % 2 == 0)
		ft_usleep(philo->args->eat_time / 2);
	if (pthread_create(&philo->thread, NULL, (void *)monitor, philo))
		return (NULL);
	while (1)
	{
		if (take_fork(philo))
			break ;
		philo_eating(philo);
		print(philo, philo->id, "is sleeping");
		ft_usleep(philo->args->sleep_time);
		print(philo, philo->id, "is thinking");
	}
	if (pthread_join(philo->thread, NULL))
		return (NULL);
	clean_local_sem(philo);
		return (NULL);
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
	sem_unlink("fork");
	sem_unlink("print");
	sem_unlink("die");
	sem_unlink("s");
	args->fork = sem_open("fork", O_CREAT, 0644, args->nb_philo);
	args->print = sem_open("print", O_CREAT, 0644, 1);
	args->die = sem_open("die", O_CREAT, 0644, 1);
	args->s = sem_open("s", O_CREAT, 0644, 0);
	return (0);
}

int	clean_up(t_philo_args *args, t_philo *philos, pid_t *pids)
{
	int	i;

	sem_close(args->fork);
	sem_close(args->print);
	sem_close(args->die);
	sem_close(args->s);
	sem_unlink("fork");
	sem_unlink("print");
	sem_unlink("die");
	sem_unlink("s");
	free(philos);
	free(pids);
	return (0);
}

void	wait_and_kill(pid_t *pids, int nb_philo)
{
	int	i;
	int	status;

	i = 0;
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status) != 0)
		{
			i = -1;
			while (++i < nb_philo)
				kill(pids[i], SIGKILL);
			break ;
		}
		i++;
	}
}

int	main(int ac, char *av[])
{
	pthread_t		monitor;
	t_philo			*philos;
	t_philo_args	args;
	int				i;
	int				status;

	if (ac < 5 || ac > 6)
		return (write(2, "Error\n", 6));
	if (check_args(&args, av))
		return (write(2, "Error\n", 6));
	if (init_data(&args))
		return (write(2, "Error\n", 6));
	philos = init_philos(&args);
	if (!philos)
		return (write(2, "Error\n", 6));
	args.pids = malloc(sizeof(pid_t) * args.nb_philo);
	if (!args.pids)
		return (write(2, "Error\n", 6));
	i = 0;
	while (i < args.nb_philo)
	{
		args.pids[i] = fork();
		if (args.pids[i] == -1)
		{
			free(philos);
			return (write(2, "Error\n", 6));
		}
		if (args.pids[i] == 0)
		{
			philo_routine(&philos[i]);
			exit(0);
		}
		i++;
		if (i == args.nb_philo)
		{
			i = -1;
			while (++i < args.nb_philo)
				sem_post(args.s);
			break ;
		}
	}
	wait_and_kill(args.pids, args.nb_philo);
	if (clean_up(&args, philos, args.pids))
		return (write(2, "Error\n", 6));
	return (0);
}
