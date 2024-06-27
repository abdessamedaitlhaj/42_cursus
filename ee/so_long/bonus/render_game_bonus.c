/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_game_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 15:46:26 by aait-lha          #+#    #+#             */
/*   Updated: 2024/05/31 17:52:23 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	put_floor(t_game *game)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	k = -1;
	while (++i < game->height)
	{
		j = -1;
		while (++j < game->width)
		{
			mlx_put_image_to_window(game->mlx, game->mlx_win, \
			game->floor_img, j * TILES, i * TILES);
			if (game->map[i][j] == 'C')
			{
				game->collectibles[++k].x = j;
				game->collectibles[k].y = i;
			}
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
	int	k;

	i = -1;
	k = -1;
	while (++i < game->height)
	{
		j = -1;
		while (++j < game->width)
		{
			if (game->map[i][j] == 'P')
				put_tile(game, 'P', game->tile_x, game->tile_y);
			else if (game->map[i][j] == '1')
				put_tile(game, '1', j * TILES, i * TILES);
			else if (game->map[i][j] == 'E')
				put_tile(game, 'E', j * TILES, i * TILES);
			else if (game->map[i][j] == 'X')
			{
				game->patrol[++k].x = j;
				game->patrol[k].y = i;
			}
		}
	}
}

void	put_enemies(t_game *game)
{
	int	i;

	i = -1;
	while (++i < game->enemies)
	{
		if (game->c1 == ANIMATION_SPEED * 10)
			game->c1 = 0;
		mlx_put_image_to_window(game->mlx, game->mlx_win, \
		game->patrol_imgs[game->c1 / ANIMATION_SPEED], \
			game->patrol[i].x * TILES, game->patrol[i].y * TILES);
	}
	game->c1++;
}

void	put_collectibles(t_game *game)
{
	int	i;

	i = -1;
	while (++i < game->components.collectibles)
	{
		if (game->c2 == ANIMATION_SPEED * 8)
			game->c2 = 0;
		mlx_put_image_to_window(game->mlx, game->mlx_win, \
		game->collectible_imgs[game->c2 / ANIMATION_SPEED], \
		game->collectibles[i].x * TILES, game->collectibles[i].y * TILES);
	}
	game->c2++;
}
