/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils10.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 03:39:54 by osarsar           #+#    #+#             */
/*   Updated: 2023/09/05 03:40:55 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lexer	*find_matching_quote(t_lexer *start, t_token tok)
{
	t_lexer	*temp;

	temp = NULL;
	if (start->next)
		temp = start->next;
	while (temp && temp->token != tok)
		temp = temp->next;
	return (temp);
}

void	tokenize_redirections(t_lexer **head)
{
	t_lexer	*temp;

	temp = *head;
	while (temp)
	{
		if (temp->token == APPEND)
		{
			ft_free(temp->cmd);
			temp->cmd = ft_strdup(">>");
			ft_delete_node(head, temp->next);
		}
		else if (temp->token == HEREDOC)
		{
			ft_free(temp->cmd);
			temp->cmd = ft_strdup("<<");
			ft_delete_node(head, temp->next);
		}
		if (temp)
			temp = temp->next;
	}
}

void	ft_lexer(char *input, t_lexer **head)
{
	int		i;

	i = 0;
	while (input[i])
	{
		ft_lstadd_back_lex(head, ft_lstnew_lex(ft_substr(input, i, 1),
				which_token(input[i], input[i + 1])));
		i++;
	}
	concat_word_lexer(head);
	tokenize_redirections(head);
}
