/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 21:26:51 by osarsar           #+#    #+#             */
/*   Updated: 2023/09/01 02:26:11 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_path(void)
{
	t_env	*env;

	env = g_glb.env;
	while (env)
	{
		if (!ft_strcmp(env->key, "PATH"))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int	ft_execve(t_cmd *data,char **envp)
{

	if (!data || !data->cmd || !*data->cmd)
		return (1);
	data->join = ft_strjoin(data->join, *data->cmd);
	if (access(data->join, F_OK) == 0)
	{
		execve(data->join, data->cmd, envp);
		return (perror("minishell "), exit(1), 1);
	}
	return(0);
}

int	ft_execve_valid_path(t_cmd *data)
{
	int		i;
	char	*path;
	char	**split_path;
	char	**envp;

	i = 0;
	if (!data || !data->cmd || !*data->cmd)
		return (1);
	envp =  env_to_char();
	if(data->cmd && data->cmd[0] && (data->cmd[0][0] == '/' || data->cmd[0][0] == '.' ))
	{
		execve(*data->cmd, data->cmd, envp);
		return (perror("minishell "), g_glb.exit_status = 127, exit(1), 1);
	}
	path = find_path();
	if (!path)
		return(ft_putstr_fd(2, "minishell : No such file or directory\n"), exit(1), 1);
	split_path = ft_split(path, ':');
	while (split_path[i])
	{
		data->join = ft_strjoin(split_path[i], "/");
		ft_execve(data, envp);
		i++;
	}
	return (ft_putstr_fd(2, "minishellf : command not found\n"), g_glb.exit_status = 127, exit(127), 0);
}

void	execution(t_cmd **node)
{
	t_cmd	*data;

	data = *node;
	if (!data || !data->cmd || !data->cmd[0])
		return ;
	if (data->cmd && *data->cmd && !ft_strcmp(*data->cmd, "echo"))
		echo_cmd(&data);
	else if (!ft_strcmp(*data->cmd, "cd"))
		cd_cmd(&data);
	else if (!ft_strcmp(*data->cmd, "env"))
		env_cmd();
	else if (!ft_strcmp(*data->cmd, "export"))
		export_cmd(data);
	else if (!ft_strcmp(*data->cmd, "unset"))
		unset_cmd(data);
	else if (!ft_strcmp(*data->cmd, "pwd"))
		pwd_cmd();
	return ;
}

void	ft_process(t_cmd *data, int fd[2])
{
	(void)fd;
	if (data->fd[0] != -2)
	{
		dup2(data->fd[0], 0);
		close(data->fd[0]);
	}
	if (data->fd[1] != -2)
	{
		dup2(data->fd[1], 1);
		close(data->fd[1]);
	}
	if (!is_builting(data))
	{
		execution(&data);
		exit(0);
	}
	else if (data->cmd)
		ft_execve_valid_path(data);
}
