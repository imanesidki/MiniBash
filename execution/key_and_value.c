/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_and_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 20:10:53 by osarsar           #+#    #+#             */
/*   Updated: 2023/08/20 00:59:30 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	affect_value(t_cmd *head, t_env	*headexp, char *value, int i)
{
	if (i == 2)
	{
		headexp->value = value;
		headexp->line = *head->cmd;
	}
	else if (i == 1)
	{
		headexp->value = ft_strjoin(headexp->value, value);
		headexp->line = *head->cmd;
	}
}

int	add_key(t_cmd *head, char *key, char *value, int i)
{
	t_env	*headexp;
	t_env	*tab;

	headexp = g_glb.env;
	while (headexp)
	{
		if (!ft_strcmp(headexp->key, key))
		{
			affect_value(head, headexp, value, i);
			return (0);
		}
		headexp = headexp->next;
	}
	tab = ft_lstnew_2(*head->cmd, key, value);
	ft_lstadd_back_2(&g_glb.env, tab);
	return (0);
}

int	keycmp_continue(t_cmd *head, char *key, char *value, int i)
{
	char	*path;

	path = key;
	if (!ft_strcmp(key, ""))
	{
		ft_put_str_error(*head->cmd);
		return (-1);
	}
	while (*path)
	{
		if (!ft_isalpha(*path))
		{
			ft_put_str_error(*head->cmd);
			return (-1);
		}
		path++;
	}
	add_key(head, key, value, i);
	return (0);
}

int	keycmp(t_cmd *head, char *key, char *value)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(*head->cmd) - ft_strlen(value);
	if (check_key(key) == -1)
	{
		ft_put_str_error(*head->cmd);
		return (-1);
	}
	else if (check_key(key) == 1)
	{
		i = 1;
		key = ft_substr(*head->cmd, 0, len - 2);
	}
	else if (check_key(key) == 2)
	{
		i = 2;
		key = ft_substr(*head->cmd, 0, len - 1);
	}
	else
		key = *head->cmd;
	keycmp_continue(head, key, value, i);
	return (0);
}
