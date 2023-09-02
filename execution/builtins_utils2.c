/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 19:43:05 by osarsar           #+#    #+#             */
/*   Updated: 2023/09/02 04:00:41 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset_cmd_if(t_cmd **data)
{
	t_env	*env;
	int		m;

	while (*(*data)->cmd)
	{
		env = g_glb.env;
		if (env)
		{
			m = 0;
			if (parsing_unset(data) == -1)
				continue ;
			if ((*(*data)->cmd && env->key)
				&& !ft_strcmp(*(*data)->cmd, env->key))
			{
				unset_first(data);
				continue ;
			}
			unset_middle(data, &env, &m);
			if (m == 0)
				unset_last_ex(data, &env);
		}
		else
			break ;
	}
}

int	ft_execve(t_cmd *data, char **envp)
{
	if (!data || !data->cmd || !*data->cmd)
		return (1);
	data->join = ft_strjoin(data->join, *data->cmd);
	if (access(data->join, F_OK) == 0)
	{
		execve(data->join, data->cmd, envp);
		g_glb.exit_status = 1;
		return (perror("minishell "), exit(1), 1);
	}
	return (0);
}

void	exit_cmd_utils(t_cmd *data)
{
	if (*data->cmd)
	{
		if (**data->cmd > '9' || **data->cmd < '0')
		{
			printf("exit\n");
			ft_putstr_fd(2, "minishell : exit: $: numeric argument required\n");
			g_glb.exit_status = 255;
			return ;
		}
		else
		{
			printf("exit\n");
			g_glb.exit_status = (char)ft_atoi(*data->cmd);
			exit((char)ft_atoi(*data->cmd));
		}
	}
	else
	{
		printf("exit\n");
		g_glb.exit_status = 1;
		exit(1);
	}
}

void	exit_cmd(t_cmd *data)
{
	data->cmd++;
	if (data->cmd[0] && data->cmd[1])
	{
		printf("exit\n");
		ft_putstr_fd(2, "minishell : exit: too many arguments\n");
		g_glb.exit_status = 1;
		return ;
	}
	else
		exit_cmd_utils(data);
}
