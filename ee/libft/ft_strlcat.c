/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 17:59:55 by aait-lha          #+#    #+#             */
/*   Updated: 2023/12/13 15:46:08 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t		i;
	size_t		j;
	size_t		s_len;
	size_t		t_len;

	if ((!dst || !src) && !dstsize)
		return (0);
	s_len = ft_strlen(src);
	i = 0;
	while (dst[i])
		i++;
	if (i > dstsize - 1 || !dstsize)
		return (dstsize + s_len);
	t_len = i + s_len;
	j = 0;
	while (src[j] && i < dstsize - 1)
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (t_len);
}
