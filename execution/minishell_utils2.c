/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 20:23:56 by osarsar           #+#    #+#             */
/*   Updated: 2023/08/20 01:03:53 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strlen_2(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i - 1);
}

char	*ft_value(char *str)
{
	char	*value;

	value = str;
	while (*value++ != '=' && *value)
		;
	return (value);
}

char	**env_to_char(void)
{
	t_env	*env;
	char	**str;
	int		len;
	int		i;

	i = 0;
	env = g_glb.env;
	len = lstsize();
	str = ft_calloc(sizeof(char *), len + 1);
	while (env)
	{
		str[i] = ft_strjoin(env->key, "=");
		str[i] = ft_strjoin(str[i], env->value);
		env = env->next;
		i++;
	}
	return (str);
}

t_env	*variable_environnement(char **envp)
{
	t_env	*tab;
	char	*value;
	char	*key;
	int		i;

	i = 1;
	value = ft_value(envp[0]);
	key = ft_substr(envp[0], 0, ft_strlen(envp[0]) - ft_strlen(value) - 1);
	g_glb.env = ft_lstnew_2(envp[0], key, value);
	while (envp[i])
	{
		value = ft_value(envp[i]);
		key = ft_substr(envp[i], 0, ft_strlen(envp[i]) - ft_strlen(value) - 1);
		tab = ft_lstnew_2(envp[i], key, value);
		ft_lstadd_back_2(&g_glb.env, tab);
		i++;
	}
	return (tab);
}

t_env	*duplicate_env(void)
{
	t_env	*tab;
	t_env	*str;
	t_env	*head;

	str = ft_lstnew_2(g_glb.env->line, g_glb.env->key, g_glb.env->value);
	head = g_glb.env->next;
	while (head)
	{
		tab = ft_lstnew_2(head->line, head->key, head->value);
		ft_lstadd_back_2(&str, tab);
		head = head->next;
	}
	return (str);
}
