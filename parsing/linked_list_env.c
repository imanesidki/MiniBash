/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 22:30:58 by isidki            #+#    #+#             */
/*   Updated: 2023/08/18 00:17:08 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*parcour;
	t_env	*ptr;

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
}

t_env	*ft_lstnew_env(char *key, char *value)
{
	t_env	*node;

	node = (t_env *)ft_malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

void	ft_lstclear_env(t_env **lst)
{
	t_env	*parcour;
	t_env	*l;

	if (!lst)
		return ;
	parcour = *lst;
	while (parcour)
	{
		l = parcour;
		parcour = parcour->next;
		ft_free(l->key);
		ft_free(l->value);
		free (l);
	}
	*lst = NULL;
}
