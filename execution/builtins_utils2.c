/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 19:43:05 by osarsar           #+#    #+#             */
/*   Updated: 2023/09/02 00:38:35 by osarsar          ###   ########.fr       */
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
