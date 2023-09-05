/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidki <isidki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 03:48:40 by osarsar           #+#    #+#             */
/*   Updated: 2023/09/05 16:15:52 by isidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_nbr_cmd(t_lexer *tmp)
{
	int	i;

	i = 0;
	while (tmp && tmp->token != PIPE)
	{
		if (tmp->token == WORD || tmp->token == DQU
			|| tmp->token == SQU)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

void	split_cmd(t_lexer **tmp, int i, t_lexer *hold, char ***cmnd)
{
	int	j;

	j = 0;
	*cmnd = (char **)ft_malloc((sizeof(char *) * (i + 1)));
	if (!(*cmnd))
		return ;
	(*tmp) = hold;
	while ((*tmp) && (*tmp)->token != PIPE)
	{
		if ((*tmp)->token == WORD || (*tmp)->token == DQU
			|| (*tmp)->token == SQU)
			(*cmnd)[j++] = ft_strdup((*tmp)->cmd);
		(*tmp) = (*tmp)->next;
	}
	(*cmnd)[j] = NULL;
}

void	concat_dqu_squ_word(t_lexer *tmp, t_lexer *current)
{
	char		*concatenated;
	t_lexer		*next_tmp;

	concatenated = NULL;
	while (tmp && (tmp->token == WORD || tmp->token == DQU
			|| tmp->token == SQU))
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

void	ft_concat_word_dqu_squ(t_lexer **head)
{
	t_lexer	*tmp;
	t_lexer	*current;

	current = *head;
	while (current && current->next)
	{
		if (current->token == WORD || current->token == DQU
			|| current->token == SQU)
		{
			tmp = current->next;
			concat_dqu_squ_word(tmp, current);
		}
		current = current->next;
	}
}

void	ft_split_pipe(t_lexer **head, t_cmd **cmd)
{
	t_lexer	*tmp;
	t_lexer	*hold;
	char	**cmnd;
	int		i;

	ft_file_redirect(head);
	tmp = *head;
	cmnd = NULL;
	while (tmp)
	{
		hold = tmp;
		i = ft_nbr_cmd(tmp);
		if (i > 0)
			split_cmd(&tmp, i, hold, &cmnd);
		else if (i == 0)
		{
			cmnd = NULL;
			tmp = hold;
			while (tmp && tmp->token != PIPE)
				tmp = tmp->next;
		}
		ft_lstadd_back_cmd(cmd, ft_lstnew_cmd(cmnd));
		if (tmp && tmp->token == PIPE)
			tmp = tmp->next;
	}
}
