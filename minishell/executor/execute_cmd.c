/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:16:07 by aait-lha          #+#    #+#             */
/*   Updated: 2024/08/05 20:28:57 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	fork_process(t_data *data, int i, int *fd, int *prev_fd)
{
	data->status[i].pid = fork();
	if (data->status[i].pid == -1)
	{
		close_streams(&data->fd_in, &data->fd_out, data);
		ft_close(prev_fd, data);
		close_pipe(fd, data);
		fail_error("fork", &data->allocated);
	}
	if (data->status[i].pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, sig_handler);
		dup_redir(data, i, fd, *prev_fd);
		if (is_builtin(&data->cmds[i]))
			exit(ft_exec_builtin(&data->cmds[i], data));
		else
			exec_cmd(data, &data->cmds[i]);
		exit(0);
	}
	return (0);
}

int	create_process(t_data *data, t_cmd *cmd)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		close_streams(&data->fd_in, &data->fd_out, data);
		return (1);
	}
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, sig_handler);
		exec_cmd(data, cmd);
	}
	waitpid(pid, &status, 0);
	get_status(data, status);
	return (0);
}

static void	special_case(char *cmd, t_data *data)
{
	char	*dir;
	int		len_cmd;

	len_cmd = ft_strlen(cmd);
	while (cmd[len_cmd-- - 1] == '/')
		;
	if (cmd[len_cmd - 1] == '/')
	{
		dir = ft_substr(cmd, 0, len_cmd, data);
		if (access(dir, F_OK) == 0)
			not_dir(data, cmd);
	}
	no_such_file(data, cmd);
}

void	exec_cmd(t_data *data, t_cmd *cmd)
{
	char	*path;
	char	**args;

	args = allocate_cmd_args(data, cmd);
	path = NULL;
	if (!cmd->cmd[0])
		cmd_not_found(cmd->cmd, data);
	if (ft_strchr(cmd->cmd, '/') && access(cmd->cmd, F_OK) == 0)
	{
		if (is_dir(cmd->cmd) == 1)
			dir_error(data, cmd->cmd);
		if (access(cmd->cmd, X_OK) != 0)
			perm_denied(cmd->cmd);
		path = ft_strdup(cmd->cmd, &data->allocated);
	}
	else if (ft_strchr(cmd->cmd, '/') && access(cmd->cmd, F_OK) == -1)
		special_case(cmd->cmd, data);
	else
		path = find_cmd(data, cmd->cmd);
	if (!path)
		cmd_not_found(cmd->cmd, data);
	if (execve(path, args, data->envp) == -1)
		exit(1);
}
