/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:33:37 by osarsar           #+#    #+#             */
/*   Updated: 2023/09/06 15:43:53 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_env(void)
{
	while (g_glb.env)
	{
		free(g_glb.env);
		g_glb.env = g_glb.env->next;
	}
}

void	ft_close_fd(void)
{
	int	fd;

	fd = 3;
	while (fd <= 20)
	{
		if (fstat(fd, NULL) == -1)
		{
			close(fd);
		}
		fd++;
	}
}

void	exec_cmd(t_cmd *cmd)
{
	split_ls(&cmd);
	if (cmd->cmd && cmd->cmd[0])
		execution_and_redirection(cmd);
	else
		close(cmd->fd[0]);
	ft_lstclear_cmd(&cmd);
}
