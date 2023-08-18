/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 22:50:16 by osarsar           #+#    #+#             */
/*   Updated: 2023/08/18 00:16:51 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*ft_lstnew_1(void *content, t_cmd *data)
{
	t_cmd	*a;

	a = (t_cmd *)malloc(sizeof(t_cmd));
	if (a == 0)
		return (NULL);
	a->cmd = content;
	a->next = NULL;
	a->env = data->env;
	return (a);
}

t_env	*ft_lstnew_2(void *content, void *key, void *value)
{
	t_env	*a;

	a = (t_env *)malloc(sizeof(t_env));
	if (a == 0)
		return (NULL);
	a->line = content;
	a->key = key;
	a->value = value;
	a->next = NULL;
	return (a);
}

void	ft_lstadd_back_1(t_cmd **lst, t_cmd *new)
{
	t_cmd	*last;

	last = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		new->next = NULL;
		return ;
	}
	while (last->next != NULL)
	{
		last = last->next;
	}
	last->next = new;
	new->next = NULL;
}

void	ft_lstadd_back_2(t_env **lst, t_env *new)
{
	t_env	*last;

	last = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		new->next = NULL;
		return ;
	}
	while (last->next != NULL)
	{
		last = last->next;
	}
	last->next = new;
	new->next = NULL;
}

int	lstsize(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}
