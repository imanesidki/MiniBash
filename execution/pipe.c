/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 01:28:10 by osarsar           #+#    #+#             */
/*   Updated: 2023/09/06 13:16:10 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exex_with_pipe_middle_utils(t_cmd **data, int pid, int *fd)
{
	int	i;

	i = 0;
	if ((*data)->fd[0] == -1 || (*data)->fd[1] == -1)
		i = 1;
	if ((*data)-> cmd && !ft_strcmp(*(*data)->cmd, ""))
	{
		ft_putstr_fd(2, "minishell : command not found\n");
		g_glb.exit_status = 127;
		i = 1;
	}
	if (i == 0 && (*data)->cmd)
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
}

void	exec_with_pipe_middle(t_cmd **data)
{
	int	fd[2];
	int	pid;

	pid = -1;
	while ((*data)->next)
	{
		pipe(fd);
		exex_with_pipe_middle_utils(data, pid, fd);
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
		*data = (*data)->next;
	}
}

void	check_redirections(t_cmd *data)
{
	if (data->fd[1] != -2)
	{
		dup2(data->fd[1], 1);
		close(data->fd[1]);
	}
	if (data->fd[0] != -2)
	{
		dup2(data->fd[0], 0);
		close(data->fd[0]);
	}
}

int	exec_with_pipe_last(t_cmd *data, int *pid)
{
	if (data->fd[0] == -1 || data->fd[1] == -1)
		return (-1);
	if (data-> cmd && !ft_strcmp(*data->cmd, ""))
	{
		ft_putstr_fd(2, "minishell : command not found\n");
		g_glb.exit_status = 127;
		return (1);
	}
	*pid = fork();
	if (*pid == 0)
	{
		check_redirections(data);
		if (!is_builting(data))
			return (execution(&data), exit(g_glb.exit_status), 0);
		ft_execve_valid_path(data);
	}
	return (0);
}

int	exec_with_no_pipe(t_cmd *data, int *pid)
{
	if (data->cmd && !ft_strcmp(*data->cmd, ""))
		return (-2);
	if (data->fd[0] == -1 || data->fd[1] == -1)
		return (-1);
	if (data->fd[1] != -2)
	{
		dup2(data->fd[1], 1);
		close(data->fd[1]);
	}
	if (data->fd[0] != -2)
	{
		dup2(data->fd[0], 0);
		close(data->fd[0]);
	}
	if (!is_builting(data))
		return (execution(&data), 3);
	else if (data->cmd)
	{
		*pid = fork();
		if (*pid == 0)
			ft_execve_valid_path(data);
	}
	return (0);
}
