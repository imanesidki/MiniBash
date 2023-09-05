/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidki <isidki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:26:24 by isidki            #+#    #+#             */
/*   Updated: 2023/09/05 16:08:27 by isidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_ambigs_redirect(t_lexer **head, t_lexer *dlr, t_lexer *word)
{
	t_lexer	*tmp;

	tmp = dlr;
	ft_check_env(word);
	if (!*word->cmd)
	{
		if (dlr->prev && dlr->prev->token == SPC && dlr->prev->prev)
			dlr = dlr->prev->prev;
		else if (dlr->prev)
			dlr = dlr->prev;
		if (dlr && (dlr->token == IN || dlr->token == OUT
				|| dlr->token == APPEND))
			dlr->fd = -3;
	}
	ft_delete_node(head, tmp);
}

void	empty_two_nodes(t_lexer **tmp)
{
	ft_free((*tmp)->cmd);
	(*tmp)->cmd = ft_strdup("");
	ft_free((*tmp)->next->cmd);
	(*tmp)->next->cmd = ft_strdup("");
	(*tmp) = (*tmp)->next;
}

void	ft_file_redirect(t_lexer **head)
{
	t_lexer	*tmp;

	ft_change_dlr_word(head);
	ft_concat_word_dqu_squ(head);
	tmp = *head;
	while (tmp)
	{
		if ((tmp->token == IN || tmp->token == OUT
				|| tmp->token == APPEND || tmp->token == HEREDOC)
			&& tmp->next)
		{
			if (tmp->next->token == SPC)
				tmp = tmp->next->next;
			else
				tmp = tmp->next;
			if (tmp && (tmp->token == WORD || tmp->token == DQU
					|| tmp->token == SQU))
				tmp->token = FILENAME;
		}
		if (tmp)
			tmp = tmp->next;
	}
}

t_cmd	*parsing(char *input)
{
	char	*s;
	t_lexer	*l;
	t_cmd	*cmd;
	int		fd_in_herdoc;

	l = NULL;
	cmd = NULL;
	s = ft_strtrim(input, " \t\v\n\r\f");
	free(input);
	ft_lexer(s, &l);
	if (ft_check_quotes(&l))
		return (ft_lstclear_lex(&l), NULL);
	delete_quotes(&l);
	fd_in_herdoc = ft_heredoc(&l);
	if (fd_in_herdoc == -1)
	{
		if (ft_parser(&l))
			return (g_glb.exit_status = 258, ft_lstclear_lex(&l), NULL);
		return (ft_lstclear_lex(&l), NULL);
	}
	if (ft_parser(&l))
		return (g_glb.exit_status = 258, ft_lstclear_lex(&l), NULL);
	ft_expand(&l);
	ft_split_pipe(&l, &cmd);
	return (redirections(&l, &cmd, fd_in_herdoc), ft_lstclear_lex(&l), cmd);
}
