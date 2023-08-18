/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 03:46:38 by osarsar           #+#    #+#             */
/*   Updated: 2023/08/18 00:16:54 by osarsar          ###   ########.fr       */
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
			{
				i = 1;
				printf("%s",*(*data)->cmd);
				(*data)->cmd++;
				if (*(*data)->cmd)
					printf(" ");
			}
		}
		if (j != 10)
			printf("\n");
	}
	else
		printf("\n");
}

void	cd_cmd(t_cmd **data, t_env *env)
{
	(*data)->cmd++;
	if (*(*data)->cmd)
	{
		if (!ft_strcmp(*(*data)->cmd, "~"))
		{
			if (cd_1(env) == 1)
				return ;
		}
		else if (!ft_strcmp(*(*data)->cmd, "-"))
		{
			if (cd_2(env) == 1)
				return ;
		}
		else
			if (chdir(*(*data)->cmd) < 0 || !getcwd(NULL, 0))
				return (perror("minishell "));
	}
	else
		if (cd_1(env) == 1)
			return ;
	add_pwd(&env);
}

void	env_cmd(t_env *env)
{
	t_env	*head;

	head = env;
	while (head)
	{
		if (ft_strchr(head->line, '='))
			printf("%s=%s\n", head->key, head->value);
		head = head->next;
	}
}

void	export_cmd(t_cmd *data, t_env *env)
{
	t_env	*head;

	data->cmd++;
	if (*data->cmd)
	{
		while (*data->cmd)
		{
			head = env;
			keycmp(&head, data);
			data->cmd++;
		}
	}
	else
	{
		head = env;
		lstcmp(head);
	}
}

void	unset_cmd(t_cmd *data, t_env *env)
{
	t_env *tmp;

	data->cmd++;
	//parsing
	if (*data->cmd)
	{
		// if (unset_parsing(*(*data)->cmd) == 1)
		// {
		// 	ft_putstr_fd(2, "ERORR\n");
		// 	return;
		// }
			while (*data->cmd)
			{
				printf("--->>>>%s\n", *data->cmd);
				if (!ft_strcmp(*data->cmd, env->key))
				{
					tmp = env;
					env = env->next;
					free(tmp);
					data->cmd++;
					continue;;
				}
				while (env->next->next)
				{
					if (!ft_strcmp(*data->cmd, env->next->key))
					{
						tmp = env->next;
						env->next = env->next->next;
						free(tmp);
						data->cmd++;
						continue;
					}
					env = env->next;
				}
				if (!ft_strcmp(*data->cmd, env->next->key))
				{
					tmp = env->next;
					env->next = NULL;
					free(tmp);
					data->cmd++;
					continue;
				}
				data->cmd++;
			}		
	}
	else
		return;
}

void	pwd_cmd(t_env *env)
{
	t_env	*head;
	char	*pwd;

	head = env;
	pwd = getcwd(NULL, 0);
	if (pwd)
		printf("%s\n", pwd);
	else
	{
		while (head)
		{
			if (!ft_strcmp(head->key, "PWD"))
				break ;
			head = head->next;
		}
		printf("%s\n", head->value);
	}
}
