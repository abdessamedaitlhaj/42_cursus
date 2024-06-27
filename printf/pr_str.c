/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:43:11 by aait-lha          #+#    #+#             */
/*   Updated: 2024/01/09 15:08:20 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	ft_strlen(const char *s)
{
	size_t	l;

	l = 0;
	while (s[l])
	{
		l++;
	}
	return (l);
}

int	pr_str(char *str)
{
	size_t	len;

	if (!str)
		len = write(1, "(null)", 6);
	else
	{
		len = ft_strlen(str);
		write(1, str, len);
	}
	return (len);
}
