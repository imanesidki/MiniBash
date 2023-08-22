/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:11:58 by osarsar           #+#    #+#             */
/*   Updated: 2023/08/22 01:34:52 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builting(t_cmd *data)
{
	if (!data->cmd || !data->cmd[0] || !data)
		return (1);
	if (!ft_strcmp(*data->cmd, "echo") || !ft_strcmp(*data->cmd, "cd") 
		|| !ft_strcmp(*data->cmd, "env") || !ft_strcmp(*data->cmd, "export")
		||!ft_strcmp(*data->cmd, "unset") || !ft_strcmp(*data->cmd, "exit") 
		||!ft_strcmp(*data->cmd, "pwd"))
		return (0);
	return (1);
}

int	execution_and_redirection(t_cmd *data)
{
	int	in;
	int	out;
	int	pid;

	in = dup(0);
	out = dup(1);
	signal(SIGINT, handle);
	signal(SIGQUIT, handle);
	if (data->next)
	{
		exec_with_pipe_middle(&data);
		exec_with_pipe_last(data);
	}
	else
	{
		if (exec_with_no_pipe(data) == -2)
			ft_putstr_fd(2, "minishell : command not found\n");
	}
	dup2(in, 0);
	dup2(out, 1);
	while (wait(&pid) > 0);
	return (0);
}
