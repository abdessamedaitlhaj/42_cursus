/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:49:39 by aait-lha          #+#    #+#             */
/*   Updated: 2024/05/31 16:57:45 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# define TILES			64
# define W				13
# define S				1
# define A				0
# define D				2
# define EXIT_ESC		53

typedef struct s_components
{
	int		player;
	int		exit;
	int		collectibles;
	int		wall;
}				t_components;

typedef struct s_game
{
	void			*mlx;
	void			*mlx_win;
	void			*player_img[4];
	void			*wall_img;
	void			*collectible_img;
	void			*exit_img;
	void			*floor_img;
	int				width;
	int				height;
	char			**map;
	int				player_x;
	int				player_y;
	int				tile_x;
	int				tile_y;
	int				valid;
	int				moves;
	t_components	components;
	int				dir;
	int				map_file;
}				t_game;

typedef struct check_visited
{
	int		**visited;
	int		width;
	int		height;
	int		collectibles;
}				t_visited;

void	check_path(t_game *game);
void	dfs(t_game *game, t_visited *visited, int y, int x);
int		**visited_map(t_game *game);
void	free_array(int **array, int height);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

void	validate_map(t_game *game);
void	check_map(t_game *game, char *line, int check);
void	check_componenets(t_game *game, char c);

void	error(char *message);
int		open_file(char *file);
void	check_file_extension(int argc, char *file);
void	clear_game(t_game *game, char *msg, int flag);
int		exit_game(t_game *game);

void	fill_map(t_game *game);
void	get_line(t_game *game, char *line, int i);
void	put_tiles(t_game *game);
void	put_floor(t_game *game);
void	render_game(t_game *game);
void	put_tile(t_game *game, char comp, int x, int y);

int		key_press(int keycode, t_game *game);
int		check_move(t_game *game, int keycode);
int		check_next_move(t_game *game, int x, int y);

void	init_game(t_game *game);
void	init_mlx(t_game *game);
void	init_imgs(t_game *game);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*get_next_line(t_game *game);

char	*ft_strchr(char *s, int c);
size_t	ft_strlen(char *s);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);
char	*ft_strjoin(char *s1, char *s2, t_game *game);
char	*ft_strdup(char *s1, t_game *game);

#endif