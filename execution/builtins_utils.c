/* ************************************************************************** */
/*															                */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 04:56:37 by osarsar           #+#    #+#             */
/*   Updated: 2023/08/19 00:50:16 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo_utils(t_cmd **data, int *i, int *j)
{
	char	*str;

	str = *(*data)->cmd;
	{
		str++;
		while (*str == 'n')
			str++;
		if (*str == '\0')
		{
			*j = 10;
			(*data)->cmd++;
		}
		else
		{
			printf("%s",*(*data)->cmd);
			(*data)->cmd++;
			if (*(*data)->cmd)
				printf(" ");
			*i = 1;
		}
	}
}

void	add_pwd_utils(t_env **h, t_env **h1)
{
	*h1 = g_glb.env;
	while (*h1)
	{
		if ((*h1)->key && (*h1)->value && !ft_strcmp((*h1)->key, "OLDPWD"))
			break ;
		*h1 = (*h1)->next;
	}
	*h = g_glb.env;
	while (*h)
	{
		if ((*h)->key && (*h)->value && !ft_strcmp((*h)->key, "PWD"))
			break ;
		*h = (*h)->next;
	}
}

void	add_pwd(void)
{
	t_env	*h1;
	t_env	*h;
	char	*str;

	add_pwd_utils(&h, &h1);
	if (h1 && h && h1->key && h->value && h1->value && h->key)
		h1->value = h->value;
	if (h && h->value)
	{
		str = getcwd(NULL, 0);
		if (str)
		{
			h->value = str;
			free(h->value);
		}
	}
}

int	cd_1(void)
{
	t_env	*head;

	head = g_glb.env;
	while (head)
	{
		if (!ft_strcmp(head->key, "HOME"))
			break ;
		head = head->next;
	}
	if (!head)
	{
		ft_putstr_fd(2, "minishell: cd: HOME not set\n");
		g_glb.exit_status = 1;
		return (1);
	}
	if (chdir(head->value) < 0)
	{
		perror("minishell");
		g_glb.exit_status = 1;
		return (1);
	}
	return (0);
}

int	cd_2(void)
{
	t_env	*head;

	head = g_glb.env;
	while (head)
	{
		if (!ft_strcmp(head->key, "OLDPWD"))
			break ;
		head = head->next;
	}
	if (!head)
	{
		ft_putstr_fd(2, "minishell: cd: OLDPWD not set\n");
		g_glb.exit_status = 1;
		return (1);
	}
	if (chdir(head->value) < 0)
	{
		perror("minishell");
		g_glb.exit_status = 1;
		return (1);
	}
	printf("%s\n", head->value);
	return (0);
}
