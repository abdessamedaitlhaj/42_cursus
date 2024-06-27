/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:42:17 by aait-lha          #+#    #+#             */
/*   Updated: 2023/12/05 17:54:21 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nbr_len(long int nbr)
{
	int	count;

	count = 0;
	if (nbr <= 0)
		count++;
	while (nbr)
	{
		count++;
		nbr /= 10;
	}
	return (count);
}

static void	nbr_cpy(char *s, long int nbr, int count)
{
	int	i;

	i = count;
	while (i > -1 && nbr)
	{
		s[i - 1] = nbr % 10 + 48;
		nbr /= 10;
		i--;
	}
}

char	*ft_itoa(int n)
{
	char		*s;
	int			count;
	long int	nbr;

	nbr = (long int)n;
	count = nbr_len(nbr);
	s = malloc(sizeof(char) * (count + 1));
	if (!s)
		return (NULL);
	if (nbr < 0)
	{
		s[0] = '-';
		nbr *= -1;
	}
	if (!nbr)
		s[0] = '0';
	nbr_cpy(s, nbr, count);
	s[count] = '\0';
	return (s);
}
