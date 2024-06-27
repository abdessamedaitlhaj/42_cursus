/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:10:07 by aait-lha          #+#    #+#             */
/*   Updated: 2024/05/31 18:05:29 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	exit_game(t_game *game)
{
	clear_game(game, "Game Over!", 0);
	exit(0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	check_file_extension(argc, argv[1]);
	game.map_file = open_file(argv[1]);
	init_game(&game);
	validate_map(&game);
	game.map_file = open_file(argv[1]);
	fill_map(&game);
	check_path(&game);
	init_mlx(&game);
	init_imgs(&game);
	render_game(&game);
	mlx_hook(game.mlx_win, 2, 0, &key_press, &game);
	mlx_hook(game.mlx_win, 17, 0, &exit_game, &game);
	mlx_loop(game.mlx);
}
