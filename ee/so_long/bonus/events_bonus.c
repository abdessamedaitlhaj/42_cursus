/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 01:39:42 by aait-lha          #+#    #+#             */
/*   Updated: 2024/05/29 20:19:36 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	put_string(t_game *game)
{
	char	*str;

	str = ft_itoa(game->moves, game);
	mlx_string_put(game->mlx, game->mlx_win, 30, 20, 0x00FFFFFF, str);
	free(str);
}

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
	if (game->map[y][x] == 'X')
		clear_game(game, "You Lose!", 0);
	if (game->map[y][x] == 'C')
	{
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
		{
			game->tile_x += TILES;
			game->dir = 3;
		}
		else if (keycode == EXIT_ESC)
			exit_game(game);
		game->moves++;
	}
	return (0);
}
