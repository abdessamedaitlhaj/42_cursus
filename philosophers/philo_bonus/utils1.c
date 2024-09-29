/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 08:43:42 by aait-lha          #+#    #+#             */
/*   Updated: 2024/09/04 09:54:14 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

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

int	ft_atoi(char const *str, char *flag)
{
	int			sign;
	long int	sum;

	sum = 0;
	sign = 1;
	while (*str && ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	if (!*str)
	{
		if (flag)
			*flag = 'f';
		return (0);
	}
	while (*str && ft_isdigit(*str))
	{
		sum = sum * 10 + sign * (*str - 48);
		if (sum > 2147483647)
		{
			if (flag)
				*flag = 'f';
			return (0);
		}
		if (sum < -2147483648)
		{
			if (flag)
				*flag = 'f';
			return (0);
		}
		str++;
	}
	if (*str)
	{
		if (flag)
			*flag = 'f';
		return (0);
	}
	return (sum);
}