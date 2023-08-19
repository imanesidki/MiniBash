/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 03:46:38 by osarsar           #+#    #+#             */
/*   Updated: 2023/08/19 01:12:17 by osarsar          ###   ########.fr       */
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

void	cd_cmd(t_cmd **data)
{
	(*data)->cmd++;
	if (*(*data)->cmd)
	{
		if (!ft_strcmp(*(*data)->cmd, "~"))
		{
			if (cd_1() == 1)
				return ;
		}
		else if (!ft_strcmp(*(*data)->cmd, "-"))
		{
			if (cd_2() == 1)
				return ;
		}
		else
			if (chdir(*(*data)->cmd) < 0 || !getcwd(NULL, 0))
				return (perror("minishell "));
	}
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
		return;
	while (head)
	{
		if (head->line && ft_strchr(head->line, '='))
			printf("%s=%s\n", head->key, head->value);
		head = head->next;
	}
}

void	export_cmd(t_cmd *data)
{
	t_env	*head;

	data->cmd++;
	if (*data->cmd)
	{
		while (*data->cmd)
		{
			head = g_glb.env;
			keycmp(&head, data);
			data->cmd++;
		}
	}
	else
	{
		head = g_glb.env;
		lstcmp(head);
	}
}

void	unset_cmd(t_cmd *data)
{
	t_env *env = g_glb.env;
	t_env *tmp;
	// int m=0;
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
				// printf("key = |%s|\n",env->key);
				// printf("%s\t%s\n", *data->cmd, env->key);
				if ((*data->cmd && env->key) && !ft_strcmp(*data->cmd, env->key))
				{
					puts("11111");
					tmp = env;
					env = env->next;
					free(tmp);
					data->cmd++;
					g_glb.env = env;
					// continue;
				}
			// 	while (env->next && data->cmd && *data->cmd)
			// 	{
			// 		if (*data->cmd && tmp_env->key && !ft_strcmp(*data->cmd, tmp_env->key))
			// 		{
			// 			puts("22222");
			// 			tmp = tmp_env;
			// 			tmp_env = tmp_env->next;
			// 			free(tmp);
			// 			data->cmd++;
			// 			m=1;
			// 			break;
			// 		}
			// 		tmp_env = tmp_env->next;
			// 	}
			// 	if (m==0)
			// 	{
			// 		if (*data->cmd && tmp_env->next->key && !ft_strcmp(*data->cmd, tmp_env->next->key))
			// 		{
			// 			puts("333333");
			// 			tmp = tmp_env->next;
			// 			tmp_env->next = NULL;
			// 			free(tmp);
			// 			data->cmd++;
			// 			continue;
			// 		}
			// 	if (m==0)
			// 	{
			// 		puts("444444");
			// 		data->cmd++;
			// 	}
			// }		
		}
		//zzzz*env = tmp_env;
	}
	else
		return;
}

void	pwd_cmd(void)
{
	t_env	*head;
	char	*pwd;

	head = g_glb.env;
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
