/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 08:38:43 by aait-lha          #+#    #+#             */
/*   Updated: 2024/10/04 01:03:28 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>

typedef struct s_philo_args
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meals;
	int				life_time;
	int				dead;
	int				start;
	long			start_time;
	sem_t			*fork;
	sem_t			*print;
	sem_t			*die;
}	t_philo_args;


typedef struct s_philo
{
	int				id;
	int				right_fork;
	int				left_fork;
	long			last_eat;
	int				eat_count;
	pthread_t		thread;
	t_philo_args	*args;
}	t_philo;


long	get_time(void);
int		ft_atoi(char const *str, char *flag);
void	ft_usleep(long sleep_time);
int	check_args(t_philo_args *args, char **av);

#endif