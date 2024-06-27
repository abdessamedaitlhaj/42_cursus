/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 21:42:07 by aait-lha          #+#    #+#             */
/*   Updated: 2024/06/04 22:17:16 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_pipex
{
	char	*infile;
	char	*outfile;
	char	**args;
	char	**envp;
	char	*path;
	char	*cmd;
	char	*limiter;
	int		argc;
	char	**argv;
	int		her;
}	t_pipex;

char	*find_cmd(t_pipex *pipex);
void	exec_cmd(t_pipex *pipex);
void	free_arr(char **arr);
void	push_line(int fd, char *limiter);
void	execute(t_pipex *pipex, int i, int *fd, int prev_fd);
void	create_childs(t_pipex *pipex);
int		here_doc(t_pipex *pipex, int argc);

char	*ft_strjoin_v2(char const *s1, char const *s2, const char *s3);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s);

void	set_last_cmd(char *outfile, int *fd, int her);
void	set_first_cmd(char *infile, int *fd);
void	ft_close(int *fd);
void	dup_cmd_in(int *fd, int prev_fd);
void	dup_cmd_out(int *fd);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);

char	*ft_strchr(char *s, int c);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);
char	*ft_strjoin(char *s1, char *s2);

#endif