/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 03:50:32 by osarsar           #+#    #+#             */
/*   Updated: 2023/09/05 03:57:48 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_expand(t_lexer **head)
{
	t_lexer	*current;
	t_lexer	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (no_expand_in_herdc_delim(&tmp))
			continue ;
		if (tmp->token == DLR && tmp->next)
		{
			if (tmp->next->token == WORD)
			{
				current = tmp->next;
				ft_ambigs_redirect(head, tmp, tmp->next);
				tmp = current;
			}
		}
		if (tmp->token == DLR && tmp->next && tmp->next->token == DLR)
			empty_two_nodes(&tmp);
		else if (tmp->token == DLR && !tmp->next)
			tmp->token = WORD;
		else if (tmp->token == DQU)
			look_for_dlr(tmp);
		tmp = tmp->next;
	}
}

void	ft_check_expand_in_line(char **line)
{
	int		i;
	char	*lin;
	char	*concat;

	i = 0;
	lin = *line;
	while (lin && i < ft_strlen(lin))
	{
		if (lin[i] == '$' && lin[i + 1] != '$')
		{
			concat = ft_split_concat_dqu_dlr(i, lin);
			free(lin);
			lin = concat;
			i = -1;
		}
		i++;
		if (!*lin)
			break ;
	}
	*line = lin;
}

void	ft_change_dlr_word(t_lexer **head)
{
	t_lexer	*tmp;
	t_lexer	*hold;

	tmp = *head;
	while (tmp)
	{
		hold = tmp->next;
		if (tmp->token == DLR && tmp->next && (tmp->next->token == DQU
				|| tmp->next->token == SQU))
			ft_delete_node(head, tmp);
		else if (tmp->token == DLR && tmp->prev && (tmp->prev->token == WORD
				|| tmp->prev->token == DQU || tmp->prev->token == SQU
				|| tmp->prev->token == SPC))
			tmp->token = WORD;
		if (tmp)
			tmp = hold;
	}
}
