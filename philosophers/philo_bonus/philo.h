/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 08:38:43 by aait-lha          #+#    #+#             */
/*   Updated: 2024/10/01 00:35:12 by aait-lha         ###   ########.fr       */
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

typedef struct s_philo_args
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_must_eat;
	int				life_time;
	int				dead;
	int				start;
	sem_t			*forks;
	sem_t			*print;
	sem_t			*eat;
	sem_t			*dead_sem;
	sem_t			*life_sem;
	sem_t			*start_sem;
}	t_philo_args;

typedef struct s_philo
{
	int				id;
	int				right_fork;
	int				left_fork;
	long			last_eat;
	long			start_time;
	int				eat_count;
	pthread_t		thread;
	t_philo_args	*args;
}	t_philo;


#endif