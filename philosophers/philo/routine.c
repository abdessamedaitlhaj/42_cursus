/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 17:45:12 by aait-lha          #+#    #+#             */
/*   Updated: 2024/10/04 19:13:25 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print(t_philo *philo, int id, char *str)
{
	long	now_time;

	pthread_mutex_lock(&philo->args->print);
	now_time = get_time() - philo->start_time;
	if (!get_dead(philo))
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

int	get_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->mutex_dead);
	if (philo->args->dead)
	{
		pthread_mutex_unlock(&philo->args->mutex_dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->args->mutex_dead);
	return (0);
}

void	*philo_routine(void *data)
{
	t_philo		*philo;

	philo = (t_philo *)data;
	if (philo->id % 2 == 0)
		ft_usleep(100);
	while (!get_dead(philo))
	{
		if (take_fork(philo))
			break ;
		philo_eating(philo);
		if (get_eat_count(philo) >= philo->args->nb_must_eat)
			break ;
		print(philo, philo->id, "is sleeping");
		ft_usleep(philo->args->time_to_sleep);
		print(philo, philo->id, "is thinking");
	}
	return (0);
}
