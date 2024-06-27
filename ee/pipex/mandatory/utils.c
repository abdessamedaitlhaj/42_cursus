/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 10:36:03 by aait-lha          #+#    #+#             */
/*   Updated: 2024/06/04 21:52:32 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		path = ft_strjoin(paths[i], "/", pipex->args[0]);
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
				(free_arr(pipex->args), perror("malloc errorcc"), exit(1));
		}
		else
			pipex->path = find_cmd(pipex);
	}
	if (execve(pipex->path, pipex->args, pipex->envp) == -1)
	{
		write(2, "pipex: ", 7);
		write(2, pipex->cmd, ft_strlen(pipex->cmd));
		write(2, ": command not found\n", 20);
		free_arr(pipex->args);
		exit(127);
	}
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	ft_close(int *fd)
{
	if (close(*fd) == -1)
		(perror("close"), exit(1));
}
