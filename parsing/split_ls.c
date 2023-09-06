/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidki <isidki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:46:32 by isidki            #+#    #+#             */
/*   Updated: 2023/09/06 01:48:23 by isidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	do_check_acces(t_cmd **tmp)
{
	char	**new_cmd;
	t_cmd	*head;
	int		i;

	i = 0;
	head = *tmp;
	new_cmd = ft_split_white_spc(head->cmd[0], " \t\v\n\r\f");
	while (new_cmd[i])
		i++;
	if (i != 1)
	{
		free_array2(head->cmd);
		head->cmd = ft_malloc(sizeof(char *) * (i + 1));
		i = -1;
		while (new_cmd[++i])
			head->cmd[i] = ft_strdup(new_cmd[i]);
		head->cmd[i] = NULL;
		free_array(new_cmd);
	}
	else
		free_array(new_cmd);
}

void	split_ls(t_cmd **node)
{
	t_cmd	*head;

	if (!(*node)->cmd || !(*node)->cmd[0])
		return ;
	head = *node;
	while (head)
	{
		if (head && head->cmd && head->cmd[0] && !head->cmd[1])
		{
			if (check_access(head->cmd[0]) == 1)
				do_check_acces(&head);
		}
		head = head->next;
	}
}

int	check_access2(char	**split_path, char	**new_check)
{
	char	*tmp;
	char	*join;
	int		i;

	i = -1;
	while (split_path[++i])
	{
		join = ft_strjoin(split_path[i], "/");
		tmp = ft_strdup(join);
		ft_free(join);
		join = ft_strjoin(tmp, new_check[0]);
		if (tmp)
			ft_free(tmp);
		tmp = NULL;
		if (access(join, F_OK | X_OK) == 0)
			return (free_array(split_path),
				free_array(new_check), ft_free(join), 1);
		if (join)
			ft_free(join);
		join = NULL;
	}
	return (free_array(split_path), free_array(new_check), 0);
}

int	check_access(char *check)
{
	char	**new_check;
	char	**split_path;
	char	*path;

	new_check = ft_split_white_spc(check, " \t\v\n\r\f");
	path = find_path();
	if (!path)
		return (free_array(new_check), 0);
	split_path = ft_split(path, ':');
	if (check_access2(split_path, new_check))
		return (1);
	return (0);
}
