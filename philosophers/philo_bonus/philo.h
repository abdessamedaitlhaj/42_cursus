/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 08:38:43 by aait-lha          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/10/03 18:14:56 by aait-lha         ###   ########.fr       */
=======
/*   Updated: 2024/10/01 02:59:23 by aait-lha         ###   ########.fr       */
>>>>>>> 33c6b116324d0bb8961fe5acd3c77d280108e95d
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
	int				nb_meals;
	int				life_time;
	int				dead;
	int				start;
<<<<<<< HEAD
	sem_t			*fork;
	sem_t			*print;
	sem_t			*die;
=======
	sem_t			*forks;
	sem_t			print;
	sem_t			eat;
	sem_t			dead_sem;
	sem_t			life_sem;
	sem_t			last_eat;
>>>>>>> 33c6b116324d0bb8961fe5acd3c77d280108e95d
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


<<<<<<< HEAD
=======
long	get_time(void);
void	clean_up(t_philo_args *args);
void	take_forks(t_philo *philo);
void	eat(t_philo *philo);
t_philo	*init_philos(t_philo_args *args);
int	init(t_philo_args *args, t_philo **philos);
int	check_args(t_philo_args *args, char **av);

int	ft_atoi(char const *str, char *flag);


>>>>>>> 33c6b116324d0bb8961fe5acd3c77d280108e95d

#endif