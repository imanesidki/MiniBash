/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils9.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 03:37:31 by osarsar           #+#    #+#             */
/*   Updated: 2023/09/05 04:17:31 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	delete_spc(t_lexer **head, t_lexer *temp)
{
	t_lexer	*hold;

	temp = temp->next;
	while (temp->token == SPC)
	{
		hold = temp->next;
		ft_delete_node(head, temp);
		temp = hold;
	}
}

void	delete_consctv_spaces(t_lexer **head)
{
	t_lexer	*temp;

	temp = *head;
	while (temp)
	{
		if (temp->token == SPC && temp->next
			&& temp->next->token == SPC)
			delete_spc(head, temp);
		temp = temp->next;
	}
}

void	delete_quotes(t_lexer **head)
{
	t_lexer	*current;
	t_lexer	*temp;

	current = *head;
	while (current)
	{
		if ((!ft_strcmp(current->cmd, "\'") && current->token == SQU)
			|| (!ft_strcmp(current->cmd, "\"") && current->token == DQU))
		{
			temp = current->next;
			ft_delete_node(head, current);
			current = temp;
		}
		else
			current = current->next;
	}
	delete_consctv_spaces(head);
}

void	ft_delete_node(t_lexer **head, t_lexer *node)
{
	t_lexer	*temp;

	temp = *head;
	while (temp)
	{
		if (node && temp == node)
		{
			handle_delete_node(head, node);
			break ;
		}
		if (temp)
			temp = temp->next;
	}
}
