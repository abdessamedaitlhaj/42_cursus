/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 03:38:53 by aait-lha          #+#    #+#             */
/*   Updated: 2024/05/30 16:18:13 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	init_animated_components(t_game *game)
{
	int	i;

	i = -1;
	while (++i < 10)
		game->patrol_imgs[i] = NULL;
	i = -1;
	while (++i < 8)
		game->collectible_imgs[i] = NULL;
	i = -1;
	while (++i < 4)
		game->player_img[i] = NULL;
}

void	init_game(t_game *game)
{
	init_animated_components(game);
	game->mlx = NULL;
	game->mlx_win = NULL;
	game->wall_img = NULL;
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
	game->enemies = 0;
	game->components = (t_components){0, 0, 0, 0};
	game->c1 = 0;
	game->c2 = 0;
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

void	init_imgs(t_game *game)
{
	int	w;
	int	h;

	init_character_imgs(game);
	game->wall_img = mlx_xpm_file_to_image(game->mlx, \
	"bonus/textures/wall.xpm", &w, &h);
	game->exit_img = mlx_xpm_file_to_image(game->mlx, \
	"bonus/textures/exit.xpm", &w, &h);
	game->floor_img = mlx_xpm_file_to_image(game->mlx, \
	"bonus/textures/floor.xpm", &w, &h);
	if (!game->wall_img || \
	!game->exit_img || !game->floor_img)
		clear_game(game, "Failed to load textures", 1);
	init_patrols(game);
	init_collectibles(game);
}
