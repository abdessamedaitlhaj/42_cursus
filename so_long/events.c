/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 01:39:42 by aait-lha          #+#    #+#             */
/*   Updated: 2024/05/30 16:45:33 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_next_move(t_game *game, int x, int y)
{
	if (game->map[y][x] == '1')
		return (0);
	if (game->map[y][x] == 'E')
	{
		if (game->components.collectibles == 0)
			clear_game(game, "You Win!", 0);
		return (0);
	}
	if (game->map[y][x] == 'C')
	{
		put_tile(game, '0', x * TILES, y * TILES);
		game->components.collectibles--;
		game->map[y][x] = '0';
	}
	return (1);
}

int	check_move(t_game *game, int keycode)
{
	int	x;
	int	y;
	int	f;

	f = 0;
	if (keycode != W && keycode != S && keycode != D && \
		keycode != A && keycode != EXIT_ESC)
		return (0);
	x = game->player_x;
	y = game->player_y;
	if (keycode == W)
		y--;
	if (keycode == S)
		y++;
	else if (keycode == A)
		x--;
	else if (keycode == D)
		x++;
	f = check_next_move(game, x, y);
	if (!f)
		return (0);
	game->player_x = x;
	game->player_y = y;
	return (1);
}

int	key_press(int keycode, t_game *game)
{
	if (check_move(game, keycode))
	{
		game->dir = 0;
		if (keycode == W)
			game->tile_y -= TILES;
		else if (keycode == S)
		{
			game->tile_y += TILES;
			game->dir = 1;
		}
		else if (keycode == A)
		{
			game->tile_x -= TILES;
			game->dir = 2;
		}
		else if (keycode == D)
			(1) && (game->tile_x += TILES, game->dir = 3);
		else if (keycode == EXIT_ESC)
			clear_game(game, "Game Over!", 0);
		(mlx_clear_window(game->mlx, game->mlx_win), render_game(game));
		game->moves++;
		printf("Moves: %d\n", game->moves);
	}
	return (0);
}
