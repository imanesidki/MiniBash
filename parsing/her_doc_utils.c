/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 03:41:33 by osarsar           #+#    #+#             */
/*   Updated: 2023/09/05 04:01:25 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	no_expand_in_herdc_delim(t_lexer **tmp)
{
	if ((*tmp)->prev && ((*tmp)->prev->token == HEREDOC
			|| ((*tmp)->prev->token == SPC && (*tmp)->prev->prev
				&& (*tmp)->prev->prev->token == HEREDOC)))
	{
		(*tmp) = (*tmp)->next;
		return (1);
	}
	return (0);
}

void	check_heredoc_delimiter(t_lexer *tmp, t_lexer *hold)
{
	if (tmp->token == HEREDOC && tmp->next)
	{
		hold = tmp->next;
		if (hold->token == SPC && hold->next)
			hold = hold->next;
		while (hold && (hold->token == WORD || hold->token == DQU
				|| hold->token == SQU || hold->token == DLR))
		{
			if (hold->token == DQU || hold->token == SQU)
				g_glb.dqu = 1;
			hold->token = WORD;
			if (hold)
				hold = hold->next;
		}
	}
}

t_lexer	*ft_heredoc_delimiter(t_lexer **head)
{
	t_lexer	*tmp;
	t_lexer	*hold;

	tmp = *head;
	hold = NULL;
	g_glb.sg = 0;
	while (tmp)
	{
		check_heredoc_delimiter(tmp, hold);
		if (tmp)
			tmp = tmp->next;
	}
	concat_word_lexer(head);
	tmp = find_delimiter(head);
	return (tmp);
}

void	handle_delete_node(t_lexer **head, t_lexer *node)
{
	if (node->prev && node->next)
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
	else if (!node->prev && node->next)
	{
		*head = node->next;
		node->next->prev = NULL;
	}
	if (!node->next && node->prev)
		node->prev->next = NULL;
	if (!node->next && !node->prev) 
		*head = NULL;
	ft_free(node->cmd);
	ft_free(node);
}
