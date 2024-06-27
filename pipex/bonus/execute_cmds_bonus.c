/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 22:12:42 by aait-lha          #+#    #+#             */
/*   Updated: 2024/06/05 16:00:53 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	set_last_cmd(char *outfile, int *fd, int her)
{
	int	outfile_fd;

	if (her)
	{
		outfile_fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (outfile_fd == -1)
			(ft_close(&fd[1]), perror("open outfile"), exit(1));
	}
	else
	{
		outfile_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (outfile_fd == -1)
			(ft_close(&fd[1]), perror("open outfile"), exit(1));
	}
	if (dup2(outfile_fd, 1) == -1)
		(ft_close(&fd[0]), ft_close(&fd[1]), ft_close(&outfile_fd), \
			perror("dup error"), exit(1));
	ft_close(&outfile_fd);
}

void	ft_close(int *fd)
{
	if (*fd == -1)
		return ;
	if (close(*fd) == -1)
		(perror("close"), exit(1));
	*fd = -1;
}

void	set_first_cmd(char *infile, int *fd)
{
	int	infile_fd;

	infile_fd = open(infile, O_RDONLY);
	if (infile_fd == -1)
		(ft_close(&fd[0]), ft_close(&fd[1]), \
			perror("open infile"), exit(1));
	if (dup2(infile_fd, 0) == -1)
		(ft_close(&infile_fd), ft_close(&fd[0]), ft_close(&fd[1]), \
			perror("dup error"), exit(1));
	ft_close(&infile_fd);
}

void	dup_cmd_in(int *fd, int prev_fd)
{
	if (dup2(prev_fd, 0) == -1)
		(ft_close(&fd[0]), ft_close(&fd[1]), ft_close(&prev_fd), \
			perror("dup error"), exit(1));
	ft_close(&prev_fd);
}

void	dup_cmd_out(int *fd)
{
	ft_close(&fd[0]);
	if (dup2(fd[1], 1) == -1)
		(ft_close(&fd[1]), perror("dup error"), exit(1));
	ft_close(&fd[1]);
}
