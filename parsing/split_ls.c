/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidki <isidki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:46:32 by isidki            #+#    #+#             */
/*   Updated: 2023/09/06 00:19:42 by isidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (!s1)
		s1 = ft_strdup("");
	if (!s2)
		return (NULL);
	str = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, 1);
	if (!str)
		return (NULL);
	while (s1[++i] != '\0')
		str[i] = s1[i];
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	ft_free(s1);
	s1 = NULL;
	return (str);
}

void	free_array2(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_free(str[i]);
		str[i] = NULL;
		i++;	
	}
	if (str)
		ft_free(str);
	str = NULL;
}

void	split_ls(t_cmd **cmd)
{
	t_cmd	*head;
	char	**new_cmd;
	int		i;

	head = *cmd;
	while (head)
	{
		if (head && head->cmd && head->cmd[0] && !head->cmd[1])
		{
			if (check_access(head->cmd[0]) == 1)
			{
				i = 0;
				new_cmd = ft_split_white_spc(head->cmd[0], " \t\v\n\r\f");
				while (new_cmd[i])
					i++;
				free_array2(head->cmd);
				head->cmd = ft_malloc(sizeof(char *) * (i + 1));
				i = -1;
				while (new_cmd[++i])
					head->cmd[i] = ft_strdup(new_cmd[i]);
				head->cmd[i] = NULL;
				free_array2(new_cmd);
			}
		}
		head = head->next;
	}
}

void	free_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;	
	}
	if (str)
		free(str);
	str = NULL;
}

int	check_access(char *check)
{
	char	**new_check;
	char	**split_path;
	char	*path;
	char	*join;
	int		i;

	i = -1;
	new_check = ft_split(check, ' ');
	path = find_path();
	if (!path)
		return (0);
	split_path = ft_split(path, ':');
	while (split_path[++i])
	{
		join = ft_strjoin(split_path[i], "/");
		join = ft_strjoin(join, new_check[0]);
		if (access(join, F_OK | X_OK) == 0)
			return (free_array(split_path),
				free_array(new_check), ft_free(join), 1);
		if (join)
			ft_free(join);
		join = NULL;
	}
	return (free_array(split_path), free_array(new_check), 0);
}
