/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 21:31:48 by aait-lha          #+#    #+#             */
/*   Updated: 2024/06/04 22:17:24 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_strchr(char *s, int c)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len])
		len++;
	return (len);
}

size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	i;
	int		src_l;

	if (!src)
		return (0);
	src_l = ft_strlen(src);
	if (!dstsize)
		return (src_l);
	i = 0;
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_l);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 && !s2)
		return (free(s1), s1 = NULL, NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	s = malloc(s1_len + s2_len + 1);
	if (!s)
		return (free(s1), s1 = NULL, NULL);
	ft_strlcpy(s, s1, s1_len + s2_len + 1);
	ft_strlcpy(s + s1_len, s2, s1_len + s2_len + 1);
	free(s1);
	s1 = NULL;
	return (s);
}
