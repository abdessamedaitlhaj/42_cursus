/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 10:35:41 by aait-lha          #+#    #+#             */
/*   Updated: 2024/06/05 16:22:48 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	execute(t_pipex *pipex, int i, int *fd, int prev_fd)
{
	if (i == 0)
	{
		if (!pipex->her)
			set_first_cmd(pipex->infile, fd);
	}
	else
		dup_cmd_in(fd, prev_fd);
	if (i == pipex->argc - 1)
		set_last_cmd(pipex->outfile, fd, pipex->her);
	else
		dup_cmd_out(fd);
	pipex->cmd = pipex->argv[i];
	exec_cmd(pipex);
}

void	create_childs(t_pipex *pipex)
{
	int		i;
	int		fd[2];
	pid_t	pid;
	int		prev_fd;

	prev_fd = -1;
	i = -1;
	while (++i < pipex->argc)
	{
		if (i < pipex->argc - 1)
			if (pipe(fd) == -1)
				(ft_close(&fd[0]), ft_close(&fd[1]), perror("pipe"), exit(1));
		pid = fork();
		if (pid == -1)
			(ft_close(&fd[0]), ft_close(&fd[1]), perror("fork"), exit(1));
		if (pid == 0)
			execute(pipex, i, fd, prev_fd);
		if (i > 0)
			ft_close(&prev_fd);
		if (i < pipex->argc - 1)
			(1) && (ft_close(&fd[1]), prev_fd = fd[0]);
	}
	while (wait(NULL) > 0)
		;
}

int	here_doc(t_pipex *pipex, int argc)
{
	int		fd[2];

	if (argc < 6)
		(write(2, "Usage: ./pipex here_doc lim c1 c2 ... cn file2\n", 48), \
			exit(1));
	if (pipe(fd) == -1)
		(perror("pipe"), exit(1));
	push_line(fd[1], pipex->limiter);
	ft_close(&fd[1]);
	return (fd[0]);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;
	int		fd;

	if (argc < 5)
		(write(2, "Usage: ./pipex file1 c1 c2 ... cn file2\n", 40), exit(1));
	pipex = (t_pipex){argv[1], argv[argc - 1], argv, envp, NULL, \
		NULL, NULL, 0, NULL, 0};
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		pipex.her = 1;
		pipex.limiter = argv[2];
		fd = here_doc(&pipex, argc);
		(1) && (pipex.argv = argv + 3, pipex.argc = argc - 4);
		if (dup2(fd, 0) == -1)
			(ft_close(&fd), perror("dup error"), exit(1));
		(ft_close(&fd), create_childs(&pipex));
	}
	else
	{
		pipex.argv = argv + 2;
		pipex.argc = argc - 3;
		create_childs(&pipex);
	}
	return (0);
}
