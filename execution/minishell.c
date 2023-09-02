/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:11:58 by osarsar           #+#    #+#             */
/*   Updated: 2023/09/02 03:44:37 by osarsar          ###   ########.fr       */
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
		||!ft_strcmp(*data->cmd, "pwd") || !ft_strcmp(*data->cmd, "exit"))
		return (0);
	return (1);
}

void	ft_exit_status(int *pid)
{
	int	i;
	int	num;

	waitpid(*pid, &i, 0);
	while (wait(NULL) > 0)
		;
	if (WIFEXITED(i))
		g_glb.exit_status = WEXITSTATUS(i);
	else if (WIFSIGNALED(i))
	{
		num = WTERMSIG(i) + 128;
		g_glb.exit_status = num;
	}
}

int	execution_and_redirection(t_cmd *data)
{
	int	in;
	int	out;
	int	pid;
	int	id;

	pid = -1;
	in = dup(0);
	out = dup(1);
	signal(SIGINT, handle);
	signal(SIGQUIT, handle);
	if (data->next)
	{
		exec_with_pipe_middle(&data);
		exec_with_pipe_last(data, &pid);
	}
	else
	{
		id = exec_with_no_pipe(data, &pid);
		if (id == -2)
			ft_putstr_fd(2, "minishell : command not found\n");
		else if (id == 3)
			return (0);
	}
	dup2(in, 0);
	close(in);
	dup2(out, 1);
	close(out);
	ft_exit_status(&pid);
	return (0);
}
