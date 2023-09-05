/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 03:25:31 by osarsar           #+#    #+#             */
/*   Updated: 2023/09/05 04:04:45 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	which_token(char c1, char c2)
{
	if (c1 == '|')
		return (PIPE);
	if (c1 == '>' && c2 == '>')
		return (APPEND);
	if (c1 == '<' && c2 == '<')
		return (HEREDOC);
	if (c1 == '<')
		return (IN);
	if (c1 == '>')
		return (OUT);
	if (c1 == ' ')
		return (SPC);
	if (c1 == '$')
		return (DLR);
	if (c1 == '"')
		return (DQU);
	if (c1 == '\'')
		return (SQU);
	return (WORD);
}

void	concat_words(t_lexer *tmp, t_lexer *current)
{
	t_lexer		*next_tmp;
	char		*concatenated;

	concatenated = NULL;
	while (tmp && tmp->token == WORD)
	{
		concatenated = ft_strjoin(current->cmd, tmp->cmd);
		if (!concatenated)
			break ;
		ft_free(current->cmd);
		current->cmd = concatenated;
		next_tmp = tmp->next;
		if (tmp->next)
			next_tmp->prev = current;
		ft_free(tmp->cmd);
		ft_free(tmp);
		tmp = next_tmp;
	}
	current->next = tmp;
}

void	concat_word_lexer(t_lexer **l)
{
	t_lexer	*current;
	t_lexer	*tmp;

	current = *l;
	while (current && current->next)
	{
		if (current->token == WORD)
		{
			tmp = current->next;
			concat_words(tmp, current);
		}
		current = current->next;
	}
}

void	concat_between_qu(t_lexer *start, t_lexer *end, t_token tok)
{
	t_lexer	*current;
	t_lexer	*tmp;
	char	*concatenated;

	current = start;
	current->token = tok;
	tmp = start->next;
	while (tmp && tmp != end) 
	{
		concatenated = ft_strjoin(current->cmd, tmp->cmd);
		if (!concatenated)
			break ;
		ft_free (current->cmd);
		current->cmd = concatenated;
		current->token = tok;
		current->next = tmp->next;
		if (tmp->next)
			tmp->next->prev = current;
		ft_free(tmp->cmd);
		ft_free(tmp);
		if (current->next)
			tmp = current->next;
		else
			return ;
	}
}

int	unexpected_tok(t_lexer *tmp)
{
	if ((tmp->token == IN || tmp->token == OUT
			|| tmp->token == APPEND || tmp->token == HEREDOC)
		&& tmp->next && ((tmp->next->token != WORD
				&& tmp->next->token != DQU && tmp->next->token != SQU
				&& tmp->next->token != DLR && tmp->next->token != SPC)
			|| (tmp->next->token == SPC && tmp->next->next
				&& tmp->next->next->token != WORD
				&& tmp->next->next->token != DQU
				&& tmp->next->next->token != SQU 
				&& tmp->next->next->token != DLR)))
	{
		ft_putstr_fd(2, "minishell: syntax error near unexpected token\n");
		return (1);
	}
	return (0);
}
