/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_imgs_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:21:47 by aait-lha          #+#    #+#             */
/*   Updated: 2024/05/30 16:17:45 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	init_patrols2(t_game *game)
{
	int	w;
	int	h;

	game->patrol_imgs[5] = mlx_xpm_file_to_image(game->mlx, \
	"bonus/textures/patrol5.xpm", &w, &h);
	game->patrol_imgs[6] = mlx_xpm_file_to_image(game->mlx, \
	"bonus/textures/patrol6.xpm", &w, &h);
	game->patrol_imgs[7] = mlx_xpm_file_to_image(game->mlx, \
	"bonus/textures/patrol7.xpm", &w, &h);
	game->patrol_imgs[8] = mlx_xpm_file_to_image(game->mlx, \
	"bonus/textures/patrol8.xpm", &w, &h);
	game->patrol_imgs[9] = mlx_xpm_file_to_image(game->mlx, \
	"bonus/textures/patrol9.xpm", &w, &h);
	if (!game->patrol_imgs[5] || !game->patrol_imgs[6] || \
	!game->patrol_imgs[7] || !game->patrol_imgs[8] || !game->patrol_imgs[9])
		clear_game(game, "Failed to load textures", 1);
}

void	init_patrols(t_game *game)
{
	int	w;
	int	h;

	game->patrol_imgs[0] = mlx_xpm_file_to_image(game->mlx, \
	"bonus/textures/patrol0.xpm", &w, &h);
	game->patrol_imgs[1] = mlx_xpm_file_to_image(game->mlx, \
	"bonus/textures/patrol1.xpm", &w, &h);
	game->patrol_imgs[2] = mlx_xpm_file_to_image(game->mlx, \
	"bonus/textures/patrol2.xpm", &w, &h);
	game->patrol_imgs[3] = mlx_xpm_file_to_image(game->mlx, \
	"bonus/textures/patrol3.xpm", &w, &h);
	game->patrol_imgs[4] = mlx_xpm_file_to_image(game->mlx, \
	"bonus/textures/patrol4.xpm", &w, &h);
	if (!game->patrol_imgs[0] || !game->patrol_imgs[1] || \
	!game->patrol_imgs[2] || !game->patrol_imgs[3] || !game->patrol_imgs[4])
		clear_game(game, "Failed to load textures", 1);
	init_patrols2(game);
}

void	init_collectibles2(t_game *game)
{
	int	w;
	int	h;

	game->collectible_imgs[5] = mlx_xpm_file_to_image(game->mlx, \
	"bonus/textures/diamand5.xpm", &w, &h);
	game->collectible_imgs[6] = mlx_xpm_file_to_image(game->mlx, \
	"bonus/textures/diamand6.xpm", &w, &h);
	game->collectible_imgs[7] = mlx_xpm_file_to_image(game->mlx, \
	"bonus/textures/diamand7.xpm", &w, &h);
	if (!game->collectible_imgs[5] || !game->collectible_imgs[6] || \
	!game->collectible_imgs[7])
		clear_game(game, "Failed to load textures", 1);
}

void	init_collectibles(t_game *game)
{
	int	w;
	int	h;

	game->collectible_imgs[0] = mlx_xpm_file_to_image(game->mlx, \
	"bonus/textures/diamand0.xpm", &w, &h);
	game->collectible_imgs[1] = mlx_xpm_file_to_image(game->mlx, \
	"bonus/textures/diamand1.xpm", &w, &h);
	game->collectible_imgs[2] = mlx_xpm_file_to_image(game->mlx, \
	"bonus/textures/diamand2.xpm", &w, &h);
	game->collectible_imgs[3] = mlx_xpm_file_to_image(game->mlx, \
	"bonus/textures/diamand3.xpm", &w, &h);
	game->collectible_imgs[4] = mlx_xpm_file_to_image(game->mlx, \
	"bonus/textures/diamand4.xpm", &w, &h);
	if (!game->collectible_imgs[0] || !game->collectible_imgs[1] || \
	!game->collectible_imgs[2] || !game->collectible_imgs[3] || \
	!game->collectible_imgs[4])
		clear_game(game, "Failed to load textures", 1);
	init_collectibles2(game);
}

void	init_character_imgs(t_game *game)
{
	int	w;
	int	h;

	game->player_img[0] = mlx_xpm_file_to_image(game->mlx, \
	"bonus/textures/up.xpm", &w, &h);
	game->player_img[1] = mlx_xpm_file_to_image(game->mlx, \
	"bonus/textures/down.xpm", &w, &h);
	game->player_img[2] = mlx_xpm_file_to_image(game->mlx, \
	"bonus/textures/left.xpm", &w, &h);
	game->player_img[3] = mlx_xpm_file_to_image(game->mlx, \
	"bonus/textures/right.xpm", &w, &h);
	if (!game->player_img[0] || !game->player_img[1] || \
	!game->player_img[2] || !game->player_img[3])
		clear_game(game, "Failed to load textures", 1);
}
