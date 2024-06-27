/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 03:51:28 by aait-lha          #+#    #+#             */
/*   Updated: 2024/05/31 16:54:35 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_map_size(t_game *game)
{
	if (game->width > 40)
		clear_game(game, "Map is too large", 1);
	if (game->height > 21)
		clear_game(game, "Map is too large", 1);
}

void	check_componenets(t_game *game, char c)
{
	if (c == 'P')
		game->components.player++;
	if (c == 'C')
		game->components.collectibles++;
	if (c == 'E')
		game->components.exit++;
	if (!c)
	{
		if (game->components.player != 1 || game->components.exit != 1)
			clear_game(game, "Map has more than one or any player / exit", 1);
		if (game->components.collectibles < 1)
			clear_game(game, "Map has no collectibles", 1);
	}
}

void	check_map(t_game *game, char *line, int check)
{
	int	i;
	int	length;

	length = ft_strlen(line);
	if (length != game->width)
		(free(line), clear_game(game, "Map is not rectangular", 1));
	i = 0;
	while (line[i])
	{
		if ((i == 0 || i == length - 1) && line[i] != '1')
			(free(line), clear_game(game, "Map is not surrounded by walls", 1));
		if (line[i] != '1' && check)
			(free(line), clear_game(game, "Map is not surrounded by walls", 1));
		if (line[i] != '1' && line[i] != '0' && line[i] != 'P' && \
			line[i] != 'C' && line[i] != 'E')
			(free(line), clear_game(game, "Map has an invalid character", 1));
		check_componenets(game, line[i]);
		i++;
	}
}

void	validate_map(t_game *game)
{
	char	*line;
	int		height;
	int		check;

	check = 1;
	height = 0;
	while (1)
	{
		line = get_next_line(game);
		if (!line)
			break ;
		if (height == 0)
		{
			game->width = ft_strlen(line);
			check_map(game, line, check);
		}
		else
			check_map(game, line, !check);
		height++;
		free(line);
	}
	game->height = height;
	check_map_size(game);
	check_componenets(game, '\0');
	close(game->map_file);
}
