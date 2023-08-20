/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils_ex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 23:52:12 by osarsar           #+#    #+#             */
/*   Updated: 2023/08/20 01:02:55 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo_utils_ex(t_cmd **data, int *i)
{
	*i = 1;
	printf("%s", *(*data)->cmd);
	(*data)->cmd++;
	if (*(*data)->cmd)
		printf(" ");
}

void	unset_first(t_cmd **data)
{
	t_env	*tmp;
	t_env	*env;

	env = g_glb.env;
	tmp = env;
	env = env->next;
	free(tmp);
	(*data)->cmd++;
	g_glb.env = env;
}

void	unset_middle_ex(t_cmd **data, t_env *head, int *m)
{
	t_env	*tmp;
	t_env	*env;

	env = head;
	tmp = env->next;
	env->next = env->next->next;
	free(tmp);
	(*data)->cmd++;
	*m = 1;
}

void	unset_last(t_cmd **data, t_env **head)
{
	t_env	*tmp;
	t_env	*env;

	env = *head;
	tmp = env->next;
	env->next = NULL;
	free(tmp);
	(*data)->cmd++;
}

int	parsing_unset(t_cmd **data)
{
	if (unset_parsing(*(*data)->cmd) == 1)
	{
		ft_put_str_error(*(*data)->cmd);
		(*data)->cmd++;
		return (-1);
	}
	return (0);
}
