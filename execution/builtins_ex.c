/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_ex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 00:53:28 by osarsar           #+#    #+#             */
/*   Updated: 2023/08/20 01:02:20 by osarsar          ###   ########.fr       */
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

void	unset_middle(t_cmd **data, t_env **env, int *m)
{
	while ((*env)->next->next && (*data)->cmd && *(*data)->cmd)
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
