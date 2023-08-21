/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:11:58 by osarsar           #+#    #+#             */
/*   Updated: 2023/08/21 01:29:37 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_builting(t_cmd *data)
{
	if (!data->cmd || !data->cmd[0] || !data)
		return (1);
	if (!ft_strcmp(*data->cmd, "echo") || !ft_strcmp(*data->cmd, "cd") ||
	!ft_strcmp(*data->cmd, "env") || !ft_strcmp(*data->cmd, "export") ||
	!ft_strcmp(*data->cmd, "unset") || !ft_strcmp(*data->cmd, "exit") ||
	!ft_strcmp(*data->cmd, "pwd"))
		return (0);
	return (1);
}

void	exec_with_pipe_middle(t_cmd **data)
{
	int	fd[2];
	int	pid;
	int	i;

	i = 0;
	while ((*data)->next)
	{
		pipe(fd);
		if ((*data)->fd[0] == -1 || (*data)->fd[1] == -1)
			i = 1;
		if ((*data)-> cmd && !ft_strcmp(*(*data)->cmd, ""))
		{
			ft_putstr_fd(2, "minishell : command not found\n");
			i = 1;
		}
		if (i == 0)
		{	
			pid = fork();
			if (pid == 0)
			{
				close(fd[0]);
				dup2(fd[1], 1);
				close(fd[1]);
				ft_process(*data, fd);
			}
		}
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
		i = 0; 
		*data = (*data)->next;
	}
}

// void	exec_with_pipe_last(t_cmd *data)
// {
// 	int pid;

// 	if (data->fd[0] == -1 || data->fd[1] == -1 )
// 		return (dup2(in, 0), dup2(out, 1), 0);
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		if (data->fd[1] != -2)
// 			dup2(data->fd[1], 1);
// 		if (data->fd[0] != -2)
// 			dup2(data->fd[0], 0);
// 		if (!is_builting(data))
// 			return (execution(&data), exit(g_glb.exit_status), 0);
// 		ft_execve_valid_path(data);
// 	}
// }

int	execution_and_redirection(t_cmd *data)
{
	int	in;
	int	out;
	int	pid;

	in = dup(0);
	out = dup(1);
	pid = -1;
	signal(SIGINT, handle);
	signal(SIGQUIT, handle);
	if (data->next)
	{
		exec_with_pipe_middle(&data);
		if (data->fd[0] == -1 || data->fd[1] == -1 )
			return (dup2(in, 0), dup2(out, 1), 0);
		pid = fork();
		if (pid == 0)
		{
			if (data->fd[1] != -2)
				dup2(data->fd[1], 1);
			if (data->fd[0] != -2)
				dup2(data->fd[0], 0);
			if (!is_builting(data))
				return (execution(&data), exit(g_glb.exit_status), 0);
			ft_execve_valid_path(data);
		}
	}
	else
	{
		if (data->cmd && !ft_strcmp(*data->cmd, ""))
			return (ft_putstr_fd(2, "minishell : command not found\n"), dup2(in, 0), dup2(out, 1), 0);	
		if (data->fd[0] == -1 || data->fd[1] == -1)
			return(dup2(in, 0), dup2(out, 1), 0);		
		if (data->fd[1] != -2)
			dup2(data->fd[1], 1);
		if (data->fd[0] != -2)
			dup2(data->fd[0], 0);
		if (!is_builting(data))
			return((execution(&data),dup2(in, 0), dup2(out,1)), 1);
		else
		{
			pid = fork();
			if (pid == 0)
				ft_execve_valid_path(data);
		}
	}
	dup2(in, 0);
	dup2(out, 1);	
	while (wait(&pid) > 0);
	return(0);
}
