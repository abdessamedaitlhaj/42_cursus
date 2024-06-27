/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 04:08:43 by aait-lha          #+#    #+#             */
/*   Updated: 2024/05/31 16:54:43 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	get_line(t_game *game, char *line, int i)
{
	int	j;

	j = 0;
	game->map[i] = malloc(sizeof(char) * game->width);
	if (!game->map[i])
		clear_game(game, "Malloc failed", 1);
	while (line[j])
	{
		if (line[j] == 'P')
		{
			game->tile_x = j * TILES;
			game->tile_y = i * TILES;
			game->player_x = j;
			game->player_y = i;
		}
		game->map[i][j] = line[j];
		j++;
	}
}

void	fill_map(t_game *game)
{
	char	*line;
	int		i;

	i = 0;
	game->map = malloc(sizeof(char *) * game->height);
	if (!game->map)
		clear_game(game, "Malloc failed", 1);
	while (1)
	{
		line = get_next_line(game);
		if (!line)
			break ;
		get_line(game, line, i);
		if (i + 1 == game->height)
			check_map(game, line, 1);
		free(line);
		i++;
	}
	close(game->map_file);
}
