/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 03:46:38 by osarsar           #+#    #+#             */
/*   Updated: 2023/09/05 07:56:46 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo_cmd(t_cmd **data)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	(*data)->cmd++;
	if (*(*data)->cmd)
	{
		while (*(*data)->cmd)
		{
			str = *(*data)->cmd;
			if (*str == '-' && *(str + 1) == 'n' && i == 0)
				echo_utils(data, &i, &j);
			else
				echo_utils_ex(data, &i);
		}
		if (j != 10)
			printf("\n");
	}
	else
		printf("\n");
}

void	cd_cmd(t_cmd **data)
{
	(*data)->cmd++;
	if (*(*data)->cmd)
		cd_cmd_if(*data);
	else
		if (cd_1() == 1)
			return ;
	add_pwd();
}

void	env_cmd(void)
{
	t_env	*head;

	head = g_glb.env;
	if (!head || !head->line)
		return ;
	while (head)
	{
		if (head->line && ft_strchr(head->line, '='))
			printf("%s=%s\n", head->key, head->value);
		head = head->next;
	}
}

void	export_cmd(t_cmd *data)
{
	char	*key;
	char	*value;
	int		len;

	data->cmd++;
	if (*data->cmd)
	{
		while (*data->cmd)
		{
			value = ft_value(*data->cmd);
			len = ft_strlen(*data->cmd) - ft_strlen(value);
			key = ft_substr(*data->cmd, 0, len);
			keycmp(data, key, value);
			data->cmd++;
		}
	}
	else if (g_glb.env)
		lstcmp();
}

void	unset_cmd(t_cmd *data)
{
	data->cmd++;
	if (*data->cmd)
		unset_cmd_if(&data);
	else
		return ;
}
