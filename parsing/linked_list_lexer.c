/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_lexer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:30:58 by isidki            #+#    #+#             */
/*   Updated: 2023/08/18 00:17:11 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstadd_back_lex(t_lexer **lst, t_lexer *new)
{
	t_lexer	*parcour;
	t_lexer	*ptr;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	parcour = *lst;
	while (parcour)
	{
		if (!parcour->next)
			ptr = parcour;
		parcour = parcour->next;
	}
	ptr->next = new;
	new->prev = ptr;
}

t_lexer	*ft_lstnew_lex(char *cmd, t_token token)
{
	t_lexer	*node;

	node = (t_lexer *)ft_malloc(sizeof(t_lexer));
	if (!node)
		return (NULL);
	node->cmd = cmd;
	node->token = token;
	node->fd = -1;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	ft_lstclear_lex(t_lexer **lst)
{
	t_lexer	*parcour;
	t_lexer	*l;

	if (!lst)
		return ;
	parcour = *lst;
	while (parcour)
	{
		l = parcour;
		parcour = parcour->next;
		ft_free(l->cmd);
		free (l);
	}
	*lst = NULL;
}
