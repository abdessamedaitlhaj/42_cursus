/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 22:15:28 by aait-lha          #+#    #+#             */
/*   Updated: 2024/10/04 19:11:59 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	ft_atoi(char const *str)
{
	long int	sum;

	sum = 0;
	while (*str && ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			return (-1);
		str++;
	}
	if (!*str)
		return (-1);
	while (*str && ft_isdigit(*str))
	{
		sum = sum * 10 + (*str - 48);
		if (sum > 2147483647)
			return (-1);
		if (sum < -2147483648)
			return (-1);
		str++;
	}
	if (*str)
		return (-1);
	return (sum);
}

int	check_args(t_philo_args *args, char **av)
{
	args->nb_philo = ft_atoi(av[1]);
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	if (args->nb_philo < 1 || args->time_to_die < 0 || \
	args->time_to_eat < 0 || \
	args->time_to_sleep < 0)
		return (1);
	if (av[5])
	{
		args->nb_must_eat = ft_atoi(av[5]);
		if (args->nb_must_eat <= 0)
			return (1);
	}
	else
		args->nb_must_eat = -1;
	if (args->time_to_die < 60 || args->time_to_eat < 60 || \
	args->time_to_sleep < 60 || args->nb_philo > 200)
		return (1);
	args->dead = 0;
	return (0);
}
