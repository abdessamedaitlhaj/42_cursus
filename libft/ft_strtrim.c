/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 18:20:24 by aait-lha          #+#    #+#             */
/*   Updated: 2023/12/04 17:57:37 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*s;
	int			i;
	int			j;
	int			len_s1;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	len_s1 = ft_strlen(s1);
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	while (ft_strchr(set, s1[len_s1 - 1]) && len_s1 > i)
		len_s1--;
	s = malloc(len_s1 - i + 1);
	if (!s)
		return (NULL);
	j = 0;
	while (i < len_s1)
		s[j++] = s1[i++];
	s[j] = '\0';
	return (s);
}
