/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils8.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isidki <isidki@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 03:29:48 by osarsar           #+#    #+#             */
/*   Updated: 2023/09/05 16:13:56 by isidki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;
	int		l;

	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	l = 0;
	str = (char *)ft_malloc(i + j + 1);
	if (!str)
		return (NULL);
	while (*s1)
		str[l++] = *s1++;
	while (*s2)
		str[l++] = *s2++;
	str[l] = '\0';
	return (str);
}

char	*ft_strtrim(char *s1, char *set)
{
	int	i;
	int	len;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	len = ft_strlen(s1) - 1;
	while (s1[i] && char_in_set(set, s1[i]))
		i++;
	while (len >= i && char_in_set(set, s1[len]))
		len--;
	if (len == -1)
		return (ft_strdup(""));
	return (ft_substr(s1, i, (len - i + 1)));
}

void	print_cmd_linked_list(t_cmd **head)
{
	t_cmd	*temp;
	int		ii;

	temp = *head;
	while (temp)
	{
		printf("-----------\n");
		ii = 0;
		while (temp->cmd && temp->cmd[ii])
			printf("|%s|\n", temp->cmd[ii++]);
		printf("cmd->fd[0]= %d\n", temp->fd[0]);
		printf("cmd->fd[1]= %d\n", temp->fd[1]);
		printf("-----------\n");
		temp = temp->next;
	}
	printf("END\n");
}

void	print_linked_list(t_lexer **head)
{
	t_lexer	*temp;

	temp = *head;
	while (temp)
	{
		printf("(%s, %d) -> ", temp->cmd, (int)temp->token);
		temp = temp->next;
	}
	printf("END\n");
}
