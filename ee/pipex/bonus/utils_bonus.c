/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 21:41:29 by aait-lha          #+#    #+#             */
/*   Updated: 2024/06/05 16:17:01 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*find_cmd(t_pipex *pipex)
{
	char	**paths;
	char	*path;
	int		i;

	i = 0;
	while (pipex->envp[i] && ft_strncmp(pipex->envp[i], "PATH=", 5) != 0)
		i++;
	if (!pipex->envp[i])
		return (NULL);
	paths = ft_split(pipex->envp[i] + 5, ':');
	if (!paths)
		(perror("malloc error"), free_arr(pipex->args), exit(1));
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin_v2(paths[i], "/", pipex->args[0]);
		if (!path)
			(free_arr(paths), perror("malloc error"), \
				free_arr(pipex->args), exit(1));
		if (access(path, F_OK | X_OK) == 0)
			return (free_arr(paths), path);
		free(path);
		i++;
	}
	return (free_arr(paths), NULL);
}

void	exec_cmd(t_pipex *pipex)
{
	pipex->args = ft_split(pipex->cmd, ' ');
	if (!pipex->args)
		(perror("malloc error"), exit(1));
	if (pipex->args[0])
	{
		if (access(pipex->args[0], F_OK | X_OK) == 0)
		{
			pipex->path = ft_strdup(pipex->args[0]);
			if (!pipex->path)
				(free_arr(pipex->args), perror("malloc error"), exit(1));
		}
		else
			pipex->path = find_cmd(pipex);
	}
	if (execve(pipex->path, pipex->args, pipex->envp) == -1)
	{
		write(2, "pipex: ", 8);
		write(2, pipex->cmd, ft_strlen(pipex->cmd));
		write(2, ": command not found\n", 20);
		free_arr(pipex->args);
		exit(127);
	}
}

void	push_line(int fd, char *limiter)
{
	char	*line;

	while (1)
	{
		write(1, "here_doc> ", 11);
		line = get_next_line(0);
		if (!line)
			break ;
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0 && \
			ft_strlen(line) - 1 == ft_strlen(limiter))
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
}
