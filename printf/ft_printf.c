/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 18:06:42 by aait-lha          #+#    #+#             */
/*   Updated: 2024/02/27 11:41:07 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

static int	right_func(int c, va_list args)
{
	int	len;

	len = 0;
	if (c == 'c')
		len = pr_char(va_arg(args, int));
	else if (c == 's')
		len = pr_str(va_arg(args, char *));
	else if (c == 'i' || c == 'd')
		len = pr_dec(va_arg(args, int));
	else if (c == 'p')
		len = pr_adr(va_arg(args, uintptr_t));
	else if (c == 'X' || c == 'x')
		len = pr_hex(va_arg(args, unsigned int), c);
	else if (c == 'u')
		len = pr_uns_nbr(va_arg(args, unsigned int));
	else if (c == '%')
		len = write(1, &c, 1);
	return (len);
}

int	ft_printf(const char *fr, ...)
{
	va_list		args;
	int			len;
	int			i;

	if (write(1, "", 0) < 0)
		return (-1);
	va_start(args, fr);
	len = 0;
	i = 0;
	while (fr[i])
	{
		if (fr[i] == '%')
		{
			i++;
			if (!fr[i])
				return (va_end(args), len);
			else if (ft_strchr("cspdixXu%", fr[i]))
				len += right_func(fr[i], args);
		}
		else
			len += write(1, &fr[i], 1);
		i++;
	}
	va_end(args);
	return (len);
}
