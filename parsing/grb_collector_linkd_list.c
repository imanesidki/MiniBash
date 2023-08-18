/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grb_collector_linkd_list.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 06:35:38 by isidki            #+#    #+#             */
/*   Updated: 2023/08/18 00:17:03 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstadd_back_garbage(t_garbage **lst, t_garbage *new)
{
	t_garbage	*parcour;
	t_garbage	*ptr;

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

t_garbage	*ft_lstnew_garbage(void *ptr)
{
	t_garbage	*node;

	node = (t_garbage *)ft_malloc(sizeof(t_garbage));
	if (!node)
		return (NULL);
	node->ptr = ptr;
	node->is_freed = 0;
	node->next = NULL;
	return (node);
}

void	ft_lstclear_garbage(t_garbage **lst)
{
	t_garbage	*parcour;
	t_garbage	*l;

	if (!lst)
		return ;
	parcour = *lst;
	while (parcour)
	{
		l = parcour;
		parcour = parcour->next;
		// if (l->garbage && *l->garbage)
		// {
		// 	while (*l->garbage)
		// 		ft_free(*l->garbage++);
		// 	ft_free(l->garbage);
		// }
		//free (l);
	}
	*lst = NULL;
}