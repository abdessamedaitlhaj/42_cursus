/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_int.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:42:54 by aait-lha          #+#    #+#             */
/*   Updated: 2024/01/09 15:07:42 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	nbr_len(int nbr)
{
	if (!nbr)
		return (0);
	return (1 + nbr_len(nbr / 10));
}

static void	put_nbr(int nbr)
{
	char	c;

	if (nbr == -2147483648)
	{
		write(1, "-2147483648", 11);
		return ;
	}
	if (nbr < 0)
	{
		nbr *= -1;
		write(1, "-", 1);
	}
	if (nbr < 10)
	{
		c = nbr + 48;
		write(1, &c, 1);
		return ;
	}
	if (nbr > 9)
	{
		put_nbr(nbr / 10);
		put_nbr(nbr % 10);
	}
}

int	pr_dec(int nbr)
{
	int	len;

	len = 0;
	if (nbr < 0)
		len++;
	if (!nbr)
		len += write(1, "0", 1);
	else
	{
		len += nbr_len(nbr);
		put_nbr(nbr);
	}
	return (len);
}
