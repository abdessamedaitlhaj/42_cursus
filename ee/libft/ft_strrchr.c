/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 13:16:16 by aait-lha          #+#    #+#             */
/*   Updated: 2023/12/05 09:11:38 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	l;

	l = ft_strlen(s);
	while (l > 0)
	{
		if (*(s + l) == (char)c)
			return ((char *)s + l);
		l--;
	}
	if (*(s + l) == (char)c)
		return ((char *)s + l);
	return (NULL);
}
