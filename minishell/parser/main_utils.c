/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 02:27:21 by ael-hara          #+#    #+#             */
/*   Updated: 2024/08/05 20:18:16 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_while(t_data *data, struct termios *term)
{
	data->allocated = NULL;
	data->fd_in = -2;
	data->fd_out = -2;
	if (tcgetattr(0, term) == -1)
	{
		perror("tcgetattr");
		exit(1);
	}
}

void	execute_and_free(t_data *data, char *line, struct termios *term)
{
	execute_cmds(data);
	free(line);
	free_allocated(&data->allocated);
	if (tcsetattr(0, TCSANOW, term) == -1)
	{
		perror("tcsetattr");
		exit(1);
	}
}

void	line_exit(t_data *data, char *line)
{
	ft_putstr_fd("exit\n", 1);
	free(line);
	free_allocated(&data->allocated);
	free_env(&data->env);
	rl_clear_history();
	exit(data->exit_status);
}

void	check_signal(t_data *data)
{
	if (g_signal_flag == 1 && data->exit_status != 1)
	{
		data->exit_status = 1;
		g_signal_flag = 0;
	}
}

int	parsing_signal(t_data *data, char *line)
{
	if (g_signal_flag == 1)
	{
		g_signal_flag = 0;
		free_allocated(&data->allocated);
		free(line);
		return (1);
	}
	return (0);
}
