/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 08:38:43 by aait-lha          #+#    #+#             */
/*   Updated: 2024/09/04 17:50:50 by aait-lha         ###   ########.fr       */
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
	int		nb_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		nb_must_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	mutex_monitor;
	int 	monitor;
	int				life_time;
}	t_philo_args;

typedef struct s_philo
{
	int				id;
	int				right_fork;
	int				left_fork;
	int				last_meal;
	long			last_eat;
	long			last_time;
	int				eat_count;
	pthread_t		thread;
	t_philo_args	*args;
	pthread_mutex_t	print;
	pthread_mutex_t	mutex_eat_cnt;
	pthread_mutex_t	mutex_last_eat;
	pthread_mutex_t	mutex_eat_count;
}	t_philo;

void	error(void);
void	free_args(char **args);
int		ft_atoi(char const *str, char *flag);
int		ft_isspace(int c);
int		ft_isdigit(int c);
char	**ft_split(char const *s, char c);


long	get_time(void);
int	checking(t_philo_args *arg);

#endif