/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 11:47:21 by aait-lha          #+#    #+#             */
/*   Updated: 2024/05/29 16:17:53 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static char	*right_str(t_game *game, char *st_var)
{
	char	*right_str;
	int		i;
	int		j;

	i = 0;
	while (st_var[i] && st_var[i] != '\n')
		i++;
	if (!st_var[i])
		return (free(st_var), st_var = NULL, NULL);
	right_str = malloc(sizeof(char) * (ft_strlen(st_var) - i + 1));
	if (!right_str)
		(free(st_var), clear_game(game, "Malloc failed", 1));
	i++;
	j = 0;
	while (st_var[i])
	{
		right_str[j] = st_var[i];
		i++;
		j++;
	}
	right_str[j] = '\0';
	free(st_var);
	return (right_str);
}

static char	*extract_line(t_game *game, char *st_var)
{
	char	*line;
	int		i;

	i = 0;
	if (!st_var[i])
		return (NULL);
	while (st_var[i] && st_var[i] != '\n')
		i++;
	if (st_var[i] == '\n')
	{
		line = malloc(sizeof(char) * (i + 2));
		if (!line)
			(free(st_var), clear_game(game, "Malloc failed", 1));
		line[i] = '\0';
		i = 0;
		while (st_var[i] && st_var[i] != '\n')
		{
			line[i] = st_var[i];
			i++;
		}
	}
	else
		line = ft_strdup(st_var, game);
	return (line);
}

static char	*read_line(t_game *game, char *st_var)
{
	char	*buffer;
	int		nb_bytes;

	nb_bytes = 1;
	buffer = malloc(((size_t)BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		(free(st_var), clear_game(game, "Malloc failed", 1));
	while (nb_bytes != 0 && !ft_strchr(st_var, '\n'))
	{
		nb_bytes = read(game->map_file, buffer, BUFFER_SIZE);
		if (nb_bytes == -1)
		{
			free(buffer);
			return (free(st_var), st_var = NULL, NULL);
		}
		buffer[nb_bytes] = '\0';
		st_var = ft_strjoin(st_var, buffer, game);
		if (!st_var)
			return (free(buffer), NULL);
	}
	free(buffer);
	return (st_var);
}

char	*get_next_line(t_game *game)
{
	char		*line;
	static char	*st_var;

	if (BUFFER_SIZE <= 0 || game->map_file < 0)
		return (NULL);
	st_var = read_line(game, st_var);
	if (!st_var)
		return (NULL);
	line = extract_line(game, st_var);
	if (!line)
		return (free(st_var), st_var = NULL, NULL);
	st_var = right_str(game, st_var);
	return (line);
}
