/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 01:02:51 by osarsar           #+#    #+#             */
/*   Updated: 2023/09/01 21:21:23 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle(int sig)
{
	if (sig == SIGQUIT)
		printf("\\Quit\n");
	if (sig == SIGINT)
	{
		rl_catch_signals = 0;
		return ;
	}
}

void	tri_lst(t_env *head)
{
	t_env	*head_n;
	char	*tmp_key;
	char	*tmp_value;
	char	*tmp_line;

	head_n = head->next;
	while (head_n)
	{
		if (ft_strcmp((head)->line, (head_n)->line) > 0)
		{
			tmp_value = (head)->value;
			tmp_key = (head)->key;
			tmp_line = (head)->line;
			(head)->value = (head_n)->value;
			(head)->key = (head_n)->key;
			(head)->line = (head_n)->line;
			(head_n)->value = tmp_value;
			(head_n)->key = tmp_key;
			(head_n)->line = tmp_line;
		}
		(head_n) = (head_n)->next;
	}
}

t_env	*lstcmp(void)
{
	t_env	*head;
	t_env	*dup_export;

	dup_export = duplicate_env();
	head = dup_export;
	while ((head)->next)
	{
		tri_lst(head);
		(head) = (head)->next;
	}
	head = dup_export;
	while (head)
	{
		if (!ft_strcmp(head->line, head->key))
		{
			printf("declare -x %s\n", head->key);
		}
		else
			printf("declare -x %s=\"%s\"\n", head->key, head->value);
		head = head->next;
	}
	return (head);
}

int	check_key(char *key)
{
	while (*key)
	{
		if (*key == '+' && *(key + 1) == '=')
			return (1);
		else if (*key == '+' && *(key + 1) != '=')
			return (-1);
		else if (*key == '=')
			return (2);
		key++;
	}
	return (0);
}

int	check_error(char *key, t_cmd *head)
{
	if (!key)
	{
		ft_put_str_error(*head->cmd);
		return (-1);
	}
	if (check_key(key) == -1)
	{
		ft_put_str_error(*head->cmd);
		return (-1);
	}
	return (0);
}
