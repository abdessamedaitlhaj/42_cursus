/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 03:38:53 by aait-lha          #+#    #+#             */
/*   Updated: 2024/05/31 16:57:38 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_game(t_game *game)
{
	game->mlx = NULL;
	game->mlx_win = NULL;
	game->player_img[0] = NULL;
	game->player_img[1] = NULL;
	game->player_img[2] = NULL;
	game->player_img[3] = NULL;
	game->wall_img = NULL;
	game->collectible_img = NULL;
	game->exit_img = NULL;
	game->floor_img = NULL;
	game->width = 0;
	game->height = 0;
	game->map = NULL;
	game->player_x = 0;
	game->player_y = 0;
	game->tile_x = 0;
	game->tile_y = 0;
	game->valid = 0;
	game->moves = 0;
	game->components = (t_components){0, 0, 0, 0};
	game->dir = 1;
}

void	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		clear_game(game, "Mlx failed", 1);
	game->mlx_win = mlx_new_window(game->mlx, game->width * TILES, \
	game->height * TILES, "so_long");
	if (!game->mlx_win)
		clear_game(game, "Mlx failed", 1);
}

void	check_imgs(t_game *game)
{
	if (game->wall_img == NULL || game->collectible_img == NULL || \
	game->exit_img == NULL || game->floor_img == NULL || \
	game->player_img[0] == NULL || game->player_img[1] == NULL || \
	game->player_img[2] == NULL || game->player_img[3] == NULL)
		clear_game(game, "Failed to load images", 1);
}

void	init_imgs(t_game *game)
{
	int	w;
	int	h;

	game->wall_img = mlx_xpm_file_to_image(game->mlx, \
	"textures/wall.xpm", &w, &h);
	game->collectible_img = mlx_xpm_file_to_image(game->mlx, \
	"textures/diamand0.xpm", &w, &h);
	game->exit_img = mlx_xpm_file_to_image(game->mlx, \
	"textures/exit.xpm", &w, &h);
	game->floor_img = mlx_xpm_file_to_image(game->mlx, \
	"textures/floor.xpm", &w, &h);
	game->player_img[0] = mlx_xpm_file_to_image(game->mlx, \
	"textures/up.xpm", &w, &h);
	game->player_img[1] = mlx_xpm_file_to_image(game->mlx, \
	"textures/down.xpm", &w, &h);
	game->player_img[2] = mlx_xpm_file_to_image(game->mlx, \
	"textures/left.xpm", &w, &h);
	game->player_img[3] = mlx_xpm_file_to_image(game->mlx, \
	"textures/right.xpm", &w, &h);
	check_imgs(game);
}
