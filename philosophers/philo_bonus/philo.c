/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 08:40:28 by aait-lha          #+#    #+#             */
/*   Updated: 2024/10/01 00:43:06 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void	*philo_routine(void *data)
{
	return (0);
}

void	clean_up(t_philo_args *args)
{
	return ;
}

int	main(int ac, char *av[])
{
	pthread_t		monitor;
	t_philo			*philos;
	t_philo_args	args;
	int				i;

	if (ac < 5 || ac > 6)
		return (write(2, "Error\n", 6));
	if (check_args(&args, av))
		return (write(2, "Error\n", 6));
	clean_up(&args);
	return (0);
}
