/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 03:45:42 by osarsar           #+#    #+#             */
/*   Updated: 2023/09/05 03:47:55 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	assign_fd(t_lexer **tmp, int *fd_in, int *fd_out, int fd_herdc)
{
	if ((*tmp)->token == OUT || (*tmp)->token == APPEND)
	{
		if (*fd_out != -2 && *fd_out != -1)
			close(*fd_out);
		*fd_out = (*tmp)->fd;
	}
	else if ((*tmp)->token == IN)
	{
		if (*fd_in != -2 && *fd_in != -1)
			close(*fd_in);
		*fd_in = (*tmp)->fd;
	}
	else if ((*tmp)->token == HEREDOC)
	{
		*fd_in = fd_herdc;
	}
	(*tmp) = (*tmp)->next;
}

void	check_redirect_open(t_lexer **tmp, t_lexer *hold, int *fd)
{
	if ((*tmp)->token == SPC)
		(*tmp) = (*tmp)->prev;
	if (((*tmp)->token == IN || (*tmp)->token == OUT
			|| (*tmp)->token == APPEND) && (*tmp)->fd == -3)
	{
		*fd = -3;
		return ;
	}
	if ((*tmp)->token == IN)
		*fd = open(hold->cmd, O_RDONLY);
	else if ((*tmp)->token == OUT)
		*fd = open(hold->cmd, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if ((*tmp)->token == APPEND)
		*fd = open(hold->cmd, O_WRONLY | O_CREAT | O_APPEND, 0644);
}

void	ft_open_files(t_lexer **temp)
{
	t_lexer	*hold;
	t_lexer	*tmp;
	int		fd;

	tmp = *temp;
	while (tmp && tmp->token != PIPE)
	{
		hold = tmp->next;
		if (hold && hold->token == FILENAME)
		{
			check_redirect_open(&tmp, hold, &fd);
			if (fd == -1)
			{
				ft_putstring_fd(2, hold->cmd, strerror(errno), 1);
				return ;
			}
			if (fd == -3)
			{
				ft_putstring_fd(2, "", " ambiguous redirect", 1);
				return ;
			}
			tmp->fd = fd;
		}
		tmp = hold;
	}
}

void	fd_cmd(t_lexer **head, t_cmd **cmd, int fd_herdc)
{
	int		fd_in;
	int		fd_out;
	t_lexer	*tmp;
	t_cmd	*cmnd;

	cmnd = *cmd;
	tmp = *head;
	while (tmp)
	{
		fd_in = -2;
		fd_out = -2;
		while (tmp && tmp->token != PIPE)
			assign_fd(&tmp, &fd_in, &fd_out, fd_herdc);
		if (cmnd)
		{
			cmnd->fd[0] = fd_in;
			cmnd->fd[1] = fd_out;
			cmnd = cmnd->next;
		}
		if (tmp && tmp->token == PIPE)
			tmp = tmp->next;
	}
}

void	redirections(t_lexer **head, t_cmd **cmd, int fd_herdc)
{
	t_lexer	*tmp;
	t_lexer	*hold;

	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	while (tmp)
	{
		while (tmp->prev && tmp->prev->token != PIPE)
			tmp = tmp->prev;
		hold = tmp;
		ft_open_files(&tmp);
		tmp = hold;
		tmp = tmp->prev;
		if (tmp && tmp->token == PIPE)
			tmp = tmp->prev;
	}
	fd_cmd(head, cmd, fd_herdc);
}
