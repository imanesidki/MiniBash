/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 03:21:46 by osarsar           #+#    #+#             */
/*   Updated: 2023/09/05 03:59:20 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	look_for_dlr(t_lexer *tmp)
{
	int		i;
	char	*concatenated;

	i = 0;
	if (tmp)
	{
		while (tmp->cmd[i]) 
		{
			if (tmp->cmd[i] == '$' && tmp->cmd[i + 1] != '$')
			{
				concatenated = ft_split_concat_dqu_dlr(i, tmp->cmd);
				ft_free(tmp->cmd);
				tmp->cmd = concatenated;
			}
			i++;
			if (!*tmp->cmd)
				break ;
		}
	}
}

void	ft_check_env(t_lexer *dlr_ptr)
{
	char	*value;

	value = ft_split_concat_dqu_dlr(-1, dlr_ptr->cmd);
	if (value)
	{
		ft_free(dlr_ptr->cmd);
		dlr_ptr->cmd = value;
	}
}

char	*ft_env_var(char *var)
{
	t_env	*temp;

	temp = g_glb.env;
	while (temp)
	{
		if (!ft_strcmp(var, temp->key))
			return (ft_strdup(temp->value));
		temp = temp->next;
	}
	return (NULL);
}

char	*concat_var(char *wrd_expd, int i, int j, char *var)
{
	char	*concatenated;
	char	*first_sub;
	char	*last_sub;

	while (wrd_expd[i] && is_identifier(wrd_expd[i]))
		i++;
	first_sub = ft_substr(wrd_expd, 0, j - 1);
	var = ft_substr(wrd_expd, j, i - j);
	last_sub = ft_substr(wrd_expd, i, ft_strlen(wrd_expd) - i);
	if (!first_sub || !var || !last_sub)
		return (NULL);
	if (ft_env_var(var))
	{
		concatenated = ft_strjoin(first_sub, ft_env_var(var));
		concatenated = ft_strjoin(concatenated, last_sub);
	}
	else if (!*first_sub && !*last_sub)
		concatenated = ft_strdup("");
	else
		concatenated = ft_strjoin(first_sub, last_sub);
	return (concatenated);
}

char	*ft_split_concat_dqu_dlr(int i, char *wrd_expd)
{
	int		j;
	char	*concatenated;
	char	*var;

	j = ++i;
	var = NULL;
	if (wrd_expd[i] == '?')
	{
		concatenated = ft_strjoin(ft_substr(wrd_expd, 0, i - 1),
				ft_itoa(g_glb.exit_status));
		concatenated = ft_strjoin(concatenated,
				ft_substr(wrd_expd, i + 1, ft_strlen(wrd_expd) - i));
		return (concatenated);
	}
	concatenated = concat_var(wrd_expd, i, j, var);
	ft_free(var);
	return (concatenated);
}
