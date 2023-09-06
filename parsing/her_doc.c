/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 03:42:42 by osarsar           #+#    #+#             */
/*   Updated: 2023/09/06 17:08:15 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lexer	*find_delimiter(t_lexer **head)
{
	t_lexer	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (tmp->token == HEREDOC && tmp->next)
		{
			if (tmp->next->token == SPC && tmp->next->next
				&& tmp->next->next->token == WORD)
				return (tmp->next->next);
			else if (tmp->next->token == WORD)
				return (tmp->next);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int	ft_readline_herdc(t_lexer **loop, t_lexer *tmp, int *fd_return)
{
	int		fds[2];
	char	*line;

	if (*fd_return > 0)
		close(*fd_return);
	if (pipe(fds) == -1)
		return (g_glb.exit_status = 1, -1);
	line = readline("> ");
	if (!line)
		(*loop) = (*loop)->next;
	while (line && ft_strcmp(line, tmp->cmd))
	{
		if (!g_glb.dqu)
			ft_check_expand_in_line(&line);
		write(fds[1], line, ft_strlen(line));
		write(fds[1], "\n", 1);
		free(line);
		line = readline("> ");
	}
	free(line);
	if (g_glb.sg == 1)
		return (close(fds[1]), close(fds[0]), -1);
	return (g_glb.dqu = 0, close(fds[1]), *fd_return = fds[0], 0);
}

int	ft_heredoc(t_lexer **head)
{
	t_lexer	*tmp;
	t_lexer	*loop;
	int		fd_return;

	fd_return = -2;
	loop = *head;
	tmp = NULL;
	while (loop)
	{
		tmp = ft_heredoc_delimiter(&loop);
		signal(SIGINT, ft_sig_handler);
		if (tmp)
		{
			if (ft_readline_herdc(&loop, tmp, &fd_return) == -1)
				return (g_glb.exit_status = 1, -1);
			if (tmp->next)
				loop = tmp->next;
			else
				break ;
		}
		else if (loop)
			loop = loop->next;
	}
	return (fd_return);
}
