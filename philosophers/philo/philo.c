/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 08:40:28 by aait-lha          #+#    #+#             */
/*   Updated: 2024/08/10 10:25:06 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

static int	is_empty(char *str)
{
	while (*str)
	{
		if (!ft_isspace(*str))
			return (0);
		str++;
	}
	return (1);
}

int	check_args(char **args)
{
	int		i;
	int		value;
	char	flag;

	i = -1;
	flag = 't';
	while (args[++i])
	{
		if (args[i][0] == '\0' || is_empty(args[i]))
			return (1);
		value = ft_atoi(args[i], &flag);
		if (flag == 'f')
			return (1);
	}
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	printf("philo %d is taked a fork\n", philo->id);
	printf("philo %d is eating\n", philo->id);
	usleep(philo->time_to_eat * 1000);
	printf("philo %d is sleeping\n", philo->id);
	usleep(philo->time_to_sleep * 1000);
	printf("philo %d is thinking\n", philo->id);
	return (NULL);
}

int	main(int ac, char *av[])
{
	pthread_t	*threads;
	t_philo		 *philo = malloc(sizeof(t_philo));

	if (ac != 6)
	{
		write (2, "agrs not set\n", 13);
		exit(1);
	}
	if (check_args(av))
		error();
	char f = 'd';

	philo->nb_philo = ft_atoi(av[1], &f);
	philo->time_to_die = ft_atoi(av[2], &f);
	philo->time_to_eat = ft_atoi(av[3], &f);
	philo->time_to_sleep = ft_atoi(av[4], &f);
	philo->nb_eat = ft_atoi(av[5], &f);

	struct timeval tv;

    if (gettimeofday(&tv, NULL) == -1) {
        perror("gettimeofday");
        return (1);
    }
	threads = malloc(sizeof(pthread_t) * philo->nb_philo);
	philo->id = 0;
	while (philo->id < philo->nb_philo)
	{
		pthread_create(&threads[philo->id], NULL, &routine, philo);
		philo->id++;
	}
	int i = 0;
	while (i < philo->nb_philo)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	return (0);
}