/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 21:26:51 by osarsar           #+#    #+#             */
/*   Updated: 2023/08/18 04:47:31 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_path(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		if (!ft_strcmp(env->key, "PATH"))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	ft_execve(t_cmd *data, t_env *env)
{
	char		**envp;
	int			len;
	int			i;

	i = 0;
	if (!data || !data->cmd || !*data->cmd)
		return ;
	len = lstsize(env);
	envp = ft_calloc(sizeof(char *), len + 1);
	while (env)
	{
		envp[i++] = ft_strdup(env->line);
		env = env->next;
	}
	if (ft_strchr(*data->cmd, '/'))
		if (access(*data->cmd, F_OK) == 0)
		{
			execve(*data->cmd, data->cmd, envp);
			exit(1);
		}
	data->join = ft_strjoin(data->join, *data->cmd);
	if (access(data->join, F_OK) == 0)
	{
		if (execve(data->join, data->cmd, envp) == -1)
		{
			perror("minishell ");
			exit(1);
		}
	}
}

int	ft_execve_valid_path(t_cmd *data, t_env *env)
{
	int		i;
	char	*path;
	char	**split_path;

	i = 0;
	path = find_path(env);
	if (!data || !data->cmd || !*data->cmd)
		return (1);
	if (!path)
	{
		if (execve(*data->cmd, data->cmd, NULL) == -1)
		{
			perror("minishell ");
			exit(1);
		}
	}
	split_path = ft_split(path, ':');
	while (split_path[i])
	{
		data->join = ft_strjoin(split_path[i], "/");
		ft_execve(data, env);
		i++;
	}
	perror("minishell ");
	exit(127);
	return (0);
}

void	execution(t_cmd **node, t_env *env)
{
	t_cmd	*data;

	data = *node;
	if (!data || !data->cmd || !data->cmd[0])
		return ;
	if (data->cmd && *data->cmd && !ft_strcmp(*data->cmd, "echo"))
		echo_cmd(&data);
	else if (!ft_strcmp(*data->cmd, "cd"))
		cd_cmd(&data, env);
	else if (!ft_strcmp(*data->cmd, "env"))
		env_cmd(env);
	else if (!ft_strcmp(*data->cmd, "export"))
		export_cmd(data, env);
	else if (!ft_strcmp(*data->cmd, "unset"))
		unset_cmd(data, env);
	else if (!ft_strcmp(*data->cmd, "pwd"))
		pwd_cmd(env);
}

void	ft_process(t_cmd *data, t_env *envp, int fd[2])
{
	(void)fd;
	if (data->fd[0] != -2)
		dup2(data->fd[0], 0);
	if (data->fd[1] != -2)
		dup2(data->fd[1], 1);
	if (!is_builting(data))
	{
		execution(&data, envp);
		exit(0);
	}
	else
		ft_execve_valid_path(data, envp);
}
