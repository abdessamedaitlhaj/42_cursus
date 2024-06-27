/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 03:51:28 by aait-lha          #+#    #+#             */
/*   Updated: 2024/05/31 17:56:01 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	check_map_size(t_game *game)
{
	if (game->width > 40)
		clear_game(game, "Map is too large", 1);
	if (game->height > 21)
		clear_game(game, "Map is too large", 1);
}

void	allocate_animated_components(t_game *game)
{
	game->collectibles = malloc(sizeof(t_coord) * \
		game->components.collectibles);
	if (!game->collectibles)
		clear_game(game, "Malloc failed", 1);
	game->patrol = malloc(sizeof(t_coord) * game->enemies);
	if (!game->patrol)
		clear_game(game, "Malloc failed", 1);
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
		clear_game(game, "Map is not rectangular", 1);
	i = -1;
	while (line[++i])
	{
		if ((i == 0 || i == length - 1) && line[i] != '1')
			clear_game(game, "Map is not surrounded by walls", 1);
		if (line[i] != '1' && check)
			clear_game(game, "Map is not surrounded by walls", 1);
		if (line[i] != '1' && line[i] != '0' && line[i] != 'P' && \
			line[i] != 'C' && line[i] != 'E' && line[i] != 'X')
			clear_game(game, "Invalid character in map", 1);
		if (line[i] == 'X')
			game->enemies++;
		check_componenets(game, line[i]);
	}
}

void	validate_map(t_game *game)
{
	char	*line;
	int		height;
	int		check;

	height = 0;
	check = 1;
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
	(check_componenets(game, '\0'), close(game->map_file));
	allocate_animated_components(game);
}
