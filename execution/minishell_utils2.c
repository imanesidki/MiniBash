/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 20:23:56 by osarsar           #+#    #+#             */
/*   Updated: 2023/08/18 00:16:35 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strlen_2(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i - 1);
}

char *ft_value(char *str)
{
	char *value;

	value = str;
	while (*value++ != '=' && *value)
	{}
	return(value);
}

t_env *variable_environnement(t_cmd *data)
{
	t_env	*env;
	t_env	*tab;
	char	*value;
	char	*key;
	int i;

	i = 1;
	value = ft_value(data->env[0]);
	key = ft_substr(data->env[0], 0, ft_strlen(data->env[0]) - ft_strlen(value) - 1);
	env = ft_lstnew_2(data->env[0], key, value);
	while (data->env[i])
	{
		value = ft_value(data->env[i]);
		key = ft_substr(data->env[i], 0, ft_strlen(data->env[i]) - ft_strlen(value) - 1);
		tab = ft_lstnew_2(data->env[i], key, value);
		ft_lstadd_back_2(&env, tab);
		// free(tab);
		i++;
	}
	return(env);
}

t_env *duplicate_env(t_env *export)
{
	t_env	*tab;
	t_env	*str;

	str = ft_lstnew_2(export->line, export->key, export->value);
	export = export->next;
	while (export)
	{
		tab = ft_lstnew_2(export->line, export->key, export->value);
		ft_lstadd_back_2(&str, tab);
		// free(tab);
		export = export->next;
	}
	return(str);
}