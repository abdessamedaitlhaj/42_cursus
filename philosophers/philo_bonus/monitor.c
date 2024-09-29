/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 22:23:02 by aait-lha          #+#    #+#             */
/*   Updated: 2024/09/29 22:27:40 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_sem(t_philo *philo)
{
	sem_unlink("sem_fork");
	sem_unlink("sem_print");
	sem_unlink("sem_die");
	philo->fork = sem_open("sem_fork", O_CREAT, 0644, philo->philo_num);
	philo->print = sem_open("sem_print", O_CREAT, 0644, 1);
	philo->die = sem_open("sem_die", O_CREAT, 0644, 1);
}

int	take_fork(t_philo *philo)
{
	if (philo->philo_num == 1)
	{
		sem_wait(philo->fork);
		philo_printf(philo, philo->id, "has taken a fork");
		sem_wait(philo->fork);
		return (1);
	}
	sem_wait(philo->fork);
	philo_printf(philo, philo->id, "has taken a fork");
	sem_wait(philo->fork);
	philo_printf(philo, philo->id, "has taken a fork");
	return (0);
}

int	make_child(t_philo *philo)
{
	pid_t	*pid;
	int		i;

	i = -1;
	pid = (pid_t *)malloc(philo->philo_num * sizeof(pid_t));
	if (!pid)
		return (1);
	philo->start_time = get_time();
	while (++i < philo->philo_num)
	{
		pid[i] = fork();
		if (pid[i] < 0)
			return (1);
		if (pid[i] == 0)
		{
			philo->id = i;
			break ;
		}
	}
	if (pid[philo->id] == 0 && !child(philo))
		return (1);
	else
		parents(philo, pid);
	free(pid);
	return (0);
}

int	child(t_philo *philo)
{
	philo->id += 1;
	philo->eat_count = 0;
	gettimeofday(&philo->time, NULL); 
	if (pthread_create(&(philo->thread), NULL, monitoring, philo)) // 모니터링 쓰레드 생성
		return (1);
	repeat(philo);
	exit(0);
	return (0);
}

void	parents(t_philo *philo, pid_t *pid)
{
	int	status;
	int	i;

	i = 0;
	while (i < philo->philo_num)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			i = 0;
			while (i < philo->philo_num)
			{
				kill(pid[i], SIGKILL);
				i++;
			}
		}
		i++;
	}
}

void	repeat(t_philo *philo)
{
	if (philo->id % 2 == 0)
		usleep(200);
	while (1)
	{
		if (get_fork(philo))
			break ;
		philo_eating(philo);
		if (philo->eat_num != 0 && philo->eat_count == philo->eat_num)
			exit (0);
		philo_printf(philo, philo->id, "is sleeping");
		ft_usleep(philo->sleep_time);
		philo_printf(philo, philo->id, "is thinking");
	}
}

void	*monitoring(void *data)
{
	t_philo		*philo;
	long		now_time;
	long		last_time;

	philo = data;
	while (1)
	{
		now_time = get_time();
		sem_wait(philo->die);
		last_time = ((size_t)philo->time.tv_sec * 1000) + \
		((size_t)philo->time.tv_usec / 1000);
		if (now_time - last_time > philo->life_time)
		{
			philo_printf(philo, philo->id, "died");
			exit(1);
		}
		sem_post(philo->die);
		usleep(100);
	}
}