/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_adr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:42:27 by aait-lha          #+#    #+#             */
/*   Updated: 2024/01/09 15:22:50 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ptr_len(uintptr_t adr)
{
	if (!adr)
		return (0);
	return (1 + ptr_len(adr / 16));
}

static void	print_hex(uintptr_t adr)
{
	char	c;

	if (adr >= 16)
	{
		print_hex(adr / 16);
		write (1, &HEX_LO[adr % 16], 1);
	}
	else
	{
		if (adr < 10)
		{
			c = adr + 48;
			write(1, &c, 1);
		}
		else
			write (1, &HEX_LO[adr], 1);
	}
}

int	pr_adr(uintptr_t adr)
{
	int	len;

	len = 0;
	if (adr)
	{
		len = write(1, "0x", 2);
		print_hex(adr);
	}
	else
		len = write(1, "0x0", 3);
	len += ptr_len(adr);
	return (len);
}
