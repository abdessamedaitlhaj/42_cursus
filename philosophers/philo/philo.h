/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 08:38:43 by aait-lha          #+#    #+#             */
/*   Updated: 2024/09/23 19:24:42 by aait-lha         ###   ########.fr       */
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
	int				dead;
	pthread_t		thread;
	t_philo_args	*args;
}	t_philo;

void	error(void);
void	free_args(char **args);
int		ft_atoi(char const *str, char *flag);
int		ft_isspace(int c);
int		ft_isdigit(int c);
char	**ft_split(char const *s, char c);
int		checking(t_philo_args *arg);


long get_time(void);
int	checking(t_philo_args *arg);
void	ft_usleep(long sleep_time);
#endif