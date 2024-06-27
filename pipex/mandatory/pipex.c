/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 10:35:41 by aait-lha          #+#    #+#             */
/*   Updated: 2024/06/05 16:23:05 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_one(t_pipex *pipex)
{
	int	in;

	in = open(pipex->infile, O_RDONLY);
	if (in == -1)
		(ft_close(&pipex->p[0]), ft_close(&pipex->p[1]), \
			perror("open infile"), exit(1));
	pipex->cmd = pipex->argv[2];
	if (dup2(in, 0) == -1 || dup2(pipex->p[1], 1) == -1)
		(ft_close(&pipex->p[0]), ft_close(&pipex->p[1]), ft_close(&in), \
			perror("dup error"), exit(1));
	(ft_close(&pipex->p[0]), ft_close(&pipex->p[1]), ft_close(&in));
	exec_cmd(pipex);
}

void	child_two(t_pipex *pipex)
{
	int	out;

	out = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out == -1)
		(ft_close(&pipex->p[0]), ft_close(&pipex->p[1]), \
			perror("open outfile"), exit(1));
	pipex->cmd = pipex->argv[3];
	if (dup2(out, 1) == -1 || dup2(pipex->p[0], 0) == -1)
		(ft_close(&pipex->p[0]), ft_close(&pipex->p[1]), ft_close(&out), \
			perror("dup error"), exit(1));
	(ft_close(&pipex->p[0]), ft_close(&pipex->p[1]), ft_close(&out));
	exec_cmd(pipex);
}

int	main(int argc, char *argv[], char *envp[])
{
	pid_t	pid[2];
	t_pipex	pipex;

	if (argc != 5)
		(write(2, "Usage: ./pipex file1 cmd1 cmd2 file2\n", 36), exit(1));
	pipex = (t_pipex){argv[1], argv[4], {0, 0}, argv, envp, NULL, NULL, NULL};
	if (pipe(pipex.p) == -1)
		(perror("pipe"), exit(1));
	pid[0] = fork();
	if (pid[0] == -1)
		(perror("fork"), exit(1));
	else if (pid[0] == 0)
		child_one(&pipex);
	pid[1] = fork();
	if (pid[1] == -1)
		(perror("fork"), exit(1));
	else if (pid[1] == 0)
		child_two(&pipex);
	(ft_close(&pipex.p[0]), ft_close(&pipex.p[1]));
	while (wait(NULL) > 0)
		;
	return (0);
}
