/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 22:15:28 by aait-lha          #+#    #+#             */
/*   Updated: 2024/09/25 22:16:28 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(t_philo_args *args, char **av)
{
	args->nb_philo = ft_atoi(av[1], NULL);
	args->time_to_die = ft_atoi(av[2], NULL);
	args->time_to_eat = ft_atoi(av[3], NULL);
	args->time_to_sleep = ft_atoi(av[4], NULL);
	if (av[5])
		args->nb_must_eat = ft_atoi(av[5], NULL);
	else
		args->nb_must_eat = -1;
	if (args->nb_philo < 1 || args->time_to_die < 0 || args->time_to_eat < 0
		|| args->time_to_sleep < 0 || (av[5] && args->nb_must_eat <= 0))
		return (1);
	args->dead = 0;
	args->start = 0;
	return (0);
}
