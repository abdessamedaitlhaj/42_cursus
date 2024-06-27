/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:26:11 by aait-lha          #+#    #+#             */
/*   Updated: 2024/05/29 18:51:02 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (i < n && str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	if (i == n)
		return (0);
	return (str1[i] - str2[i]);
}

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	int		i;

	i = ft_strlen((char *)s);
	str = (char *)s;
	while (i >= 0)
	{
		if (str[i] == c)
			return (str + i);
		i--;
	}
	return (NULL);
}

static int	ft_nbrlen(int n)
{
	int	len;

	len = 1;
	while (n >= 10)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n, t_game *game)
{
	char	*str;
	int		len;
	int		neg;

	neg = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648", game));
	if (n < 0)
	{
		neg = 1;
		n = -n;
	}
	len = ft_nbrlen(n) + neg;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		clear_game(game, "Malloc failed", 1);
	str[len] = '\0';
	while (len--)
	{
		str[len] = n % 10 + '0';
		n /= 10;
	}
	if (neg)
		str[0] = '-';
	return (str);
}
