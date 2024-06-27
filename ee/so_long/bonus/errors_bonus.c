/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:10:44 by aait-lha          #+#    #+#             */
/*   Updated: 2024/05/31 17:56:06 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	print_str(char *msg, int flag)
{
	if (flag)
		write(1, "Error\n", 6);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}

void	error(char *msg)
{
	print_str(msg, 1);
	exit(1);
}

void	check_file_extension(int argc, char *file)
{
	char	*ext;

	if (argc != 2)
		error("Usage: ./so_long map.ber");
	ext = ft_strrchr(file, '.');
	if (!ext || ft_strncmp(ext, ".ber", 5))
		error("Invalid map file");
}

int	open_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		error("Can't open the file");
	return (fd);
}

void	clear_game(t_game *game, char *msg, int flag)
{
	if (game->map)
		free_array((int **)game->map, game->height);
	if (game->mlx)
	{
		if (game->mlx_win)
			mlx_destroy_window(game->mlx, game->mlx_win);
		free(game->mlx);
	}
	close(game->map_file);
	if (flag && msg)
		print_str(msg, 1);
	else if (msg)
		print_str(msg, 0);
	exit(flag);
}
