/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 19:19:53 by isidki            #+#    #+#             */
/*   Updated: 2023/08/18 00:17:06 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new)
{
	t_cmd	*parcour;
	t_cmd	*ptr;

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

t_cmd	*ft_lstnew_cmd(char **cmd)
{
	t_cmd	*node;

	node = (t_cmd *)ft_malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->cmd = cmd;
	node->fd[0] = -2;
	node->fd[1] = -2;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	ft_lstclear_cmd(t_cmd **lst)
{
	t_cmd	*parcour;
	t_cmd	*l;

	if (!lst)
		return ;
	parcour = *lst;
	while (parcour)
	{
		l = parcour;
		parcour = parcour->next;
		if (l->cmd && *l->cmd)
		{
			while (*l->cmd)
				ft_free(*l->cmd++);
			ft_free(l->cmd);
		}
		ft_free (l);
	}
	*lst = NULL;
}
