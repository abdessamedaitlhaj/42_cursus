/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 08:38:43 by aait-lha          #+#    #+#             */
/*   Updated: 2024/09/26 22:03:15 by aait-lha         ###   ########.fr       */
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
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	mutex_last_eat;
	pthread_mutex_t	mutex_eat_count;
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

void			error(void);
void			free_args(char **args);
int				ft_atoi(char const *str, char *flag);
int				ft_isspace(int c);
int				ft_isdigit(int c);
char			**ft_split(char const *s, char c);
int				checking(t_philo_args *arg);
long			get_time(void);
int				checking(t_philo_args *arg);
void			ft_usleep(long sleep_time);
int				philo_dead(t_philo *philos);
int				get_eat_count(t_philo philo);
int				philos_eat(t_philo *philos);
void			*monitoring(void *data);
t_philo			*init_philos(t_philo_args *args);
pthread_mutex_t	*init_forks(int nb_forks);
int				init_data(t_philo_args *args, t_philo **philos);
int				check_args(t_philo_args *args, char **av);
long			last_eat(t_philo *philo);
void			print(t_philo *philo, int id, char *str);
int				take_fork(t_philo *philo);
void			philo_eating(t_philo *philo);
void			*philo_routine(void *data);
void			clean_up(t_philo_args *args);
int				get_eat_count(t_philo philo);



#endif