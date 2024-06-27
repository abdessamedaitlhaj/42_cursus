/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 03:49:56 by aait-lha          #+#    #+#             */
/*   Updated: 2024/05/30 15:51:53 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_array(int **array, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	**visited_map(t_game *game)
{
	int	**visited;
	int	i;
	int	j;

	visited = malloc(sizeof(int *) * game->height);
	if (!visited)
		clear_game(game, "Malloc failed", 1);
	i = 0;
	while (i < game->height)
	{
		visited[i] = malloc(sizeof(int) * game->width);
		if (!visited[i])
		{
			free_array(visited, i);
			clear_game(game, "Malloc failed", 1);
		}
		j = 0;
		while (j < game->width)
		{
			visited[i][j] = 0;
			j++;
		}
		i++;
	}
	return (visited);
}

void	dfs(t_game *game, t_visited *visited, int y, int x)
{
	const int	dy[4] = {1, -1, 0, 0};
	const int	dx[4] = {0, 0, 1, -1};
	int			ny;
	int			nx;
	int			i;

	visited->visited[y][x] = 1;
	if (game->map[y][x] == 'C')
		visited->collectibles -= 1;
	if (game->map[y][x] == 'E')
	{
		game->valid = 1;
		return ;
	}
	i = -1;
	while (++i < 4)
	{
		ny = y + dy[i];
		nx = x + dx[i];
		if (game->map[ny][nx] != '1' && !visited->visited[ny][nx])
			dfs(game, visited, ny, nx);
	}
}

void	check_path(t_game *game)
{
	t_visited	visited;

	visited.visited = visited_map(game);
	visited.width = game->width;
	visited.height = game->height;
	visited.collectibles = game->components.collectibles;
	dfs(game, &visited, game->player_y, game->player_x);
	if (!game->valid || visited.collectibles > 0)
	{
		free_array(visited.visited, game->height);
		clear_game(game, "Invalid path", 1);
	}
	free_array(visited.visited, game->height);
}
