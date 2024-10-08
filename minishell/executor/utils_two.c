/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hara <ael-hara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:26:39 by aait-lha          #+#    #+#             */
/*   Updated: 2024/08/01 20:18:52 by ael-hara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_env(t_env **env)
{
	t_env	*tmp;
	t_env	*next;

	tmp = *env;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		tmp = next;
	}
	*env = NULL;
}

char	*ft_strdup2(char *str, t_data *data)
{
	char	*new_str;
	int		i;

	if (!str)
		return (NULL);
	new_str = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new_str)
		fail_error("malloc failed", &data->allocated);
	i = 0;
	while (str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

char	*copy_cwd(char *cwd, t_data *data)
{
	char	*new_str;
	int		i;

	if (!cwd)
		return (NULL);
	new_str = malloc(sizeof(char) * (ft_strlen(cwd) + 1));
	if (!new_str)
		fail_error("malloc failed", &data->allocated);
	i = 0;
	while (cwd[i])
	{
		new_str[i] = cwd[i];
		i++;
	}
	new_str[i] = '\0';
	free(cwd);
	return (new_str);
}

int	ft_unsetenv(char *key, t_data *data)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (ft_strcmp(key, tmp->key) == 0)
		{
			ft_remove_env(&data->env, key);
			break ;
		}
		tmp = tmp->next;
	}
	return (0);
}
