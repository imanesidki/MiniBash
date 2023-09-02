/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_ex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 00:53:28 by osarsar           #+#    #+#             */
/*   Updated: 2023/09/02 03:39:10 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_put_str_error(char *arg)
{
	ft_putstr_fd(2, "minishell: `");
	ft_putstr_fd(2, arg);
	ft_putstr_fd(2, "' : not a valid identifier\n");
}

void	pwd_cmd(void)
{
	t_env	*head;
	char	*pwd;

	head = g_glb.env;
	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		printf("%s\n", pwd);
		free(pwd);
	}
	else
	{
		while (head)
		{
			if (head->key && head->value && !ft_strcmp(head->key, "PWD"))
				break ;
			head = head->next;
		}
		if (head && head->key && head->value)
			printf("%s\n", head->value);
	}
}

void	unset_middle(t_cmd **data, t_env **env, int *m)
{
	while ((*env)->next && (*env)->next->next && (*data)->cmd && *(*data)->cmd)
	{
		if (*(*data)->cmd && (*env)->next->key
			&& !ft_strcmp(*(*data)->cmd, (*env)->next->key))
		{
			unset_middle_ex(&(*data), (*env), m);
			break ;
		}
		(*env) = (*env)->next;
	}
}

void	unset_last_ex(t_cmd **data, t_env **env)
{
	if (*(*data)->cmd && (*env)->key
		&& !ft_strcmp(*(*data)->cmd, (*env)->next->key))
		unset_last(&(*data), env);
	else
		(*data)->cmd++;
}

void	cd_cmd_if(t_cmd *data)
{
	char	*str;

	if (!ft_strcmp(*data->cmd, "~"))
	{
		if (cd_1() == 1)
			return ;
	}
	else if (!ft_strcmp(*data->cmd, "-"))
	{
		if (cd_2() == 1)
			return ;
	}
	else
	{
		str = getcwd(NULL, 0);
		if (chdir(*data->cmd) < 0 || !str)
		{
			free(str);
			perror("minishell ");
			return (g_glb.exit_status = 1, exit(1));
		}
		free(str);
	}
}
