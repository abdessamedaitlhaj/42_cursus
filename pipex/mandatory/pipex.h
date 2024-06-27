/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 10:35:51 by aait-lha          #+#    #+#             */
/*   Updated: 2024/06/04 21:48:27 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_pipex
{
	char	*infile;
	char	*outfile;
	int		p[2];
	char	**argv;
	char	**envp;
	char	**args;
	char	*path;
	char	*cmd;
}	t_pipex;

void	child_one(t_pipex *pipex);
void	child_two(t_pipex *pipex);
void	exec_cmd(t_pipex *pipex);
void	free_arr(char **arr);
char	*find_cmd(t_pipex *pipex);
void	ft_close(int *fd);

size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2, const char *s3);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);

#endif