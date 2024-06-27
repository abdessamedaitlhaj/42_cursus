/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 15:46:26 by aait-lha          #+#    #+#             */
/*   Updated: 2024/05/30 16:47:03 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_floor(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (++i < game->height)
	{
		j = -1;
		while (++j < game->width)
		{
			mlx_put_image_to_window(game->mlx, game->mlx_win, \
			game->floor_img, j * TILES, i * TILES);
		}
	}
}

void	put_tile(t_game *game, char comp, int tile_x, int tile_y)
{
	if (comp == 'P')
		mlx_put_image_to_window(game->mlx, game->mlx_win, \
		game->player_img[game->dir], tile_x, tile_y);
	else if (comp == '1')
		mlx_put_image_to_window(game->mlx, game->mlx_win, \
		game->wall_img, tile_x, tile_y);
	else if (comp == 'C')
		mlx_put_image_to_window(game->mlx, game->mlx_win, \
		game->collectible_img, tile_x, tile_y);
	else if (comp == 'E')
		mlx_put_image_to_window(game->mlx, game->mlx_win, \
		game->exit_img, tile_x, tile_y);
	else if (comp == '0')
		mlx_put_image_to_window(game->mlx, game->mlx_win, \
		game->floor_img, tile_x, tile_y);
}

void	put_tiles(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (++i < game->height)
	{
		j = -1;
		while (++j < game->width)
		{
			if (game->map[i][j] == '1')
				put_tile(game, '1', j * TILES, i * TILES);
			else if (game->map[i][j] == 'P')
				put_tile(game, 'P', game->tile_x, game->tile_y);
			else if (game->map[i][j] == 'C')
				put_tile(game, 'C', j * TILES, i * TILES);
			else if (game->map[i][j] == 'E')
				put_tile(game, 'E', j * TILES, i * TILES);
		}
	}
}

void	render_game(t_game *game)
{
	put_floor(game);
	put_tiles(game);
}
