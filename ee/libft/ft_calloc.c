/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 19:17:13 by aait-lha          #+#    #+#             */
/*   Updated: 2023/12/13 15:10:48 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void		*block;
	size_t		t;

	t = count * size;
	if (size && t / size != count)
		return (NULL);
	block = malloc(count * size);
	if (!block)
		return (NULL);
	ft_bzero(block, size * count);
	return (block);
}
