/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 04:56:37 by osarsar           #+#    #+#             */
/*   Updated: 2023/08/18 00:47:26 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    echo_utils(t_cmd **data, int *i, int *j)
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

void	add_pwd(t_env **env)
{
	t_env *head;
	t_env *head_1;

	head = *env;
	while (head)
    {
        if (!ft_strcmp(head->key, "OLDPWD"))
            break;
        head = head->next;
    }
    head_1 = *env;
    while (head_1)
    {
        if (!ft_strcmp(head_1->key, "PWD"))
            break;
        head_1 = head_1->next;
    }
	if (head)
    	head->value = head_1->value;
    head_1->value =  getcwd(NULL, 0);
}

int	cd_1(t_env *env)
{
	t_env *head;
	head = env;

    while (head)
    {
        if (!ft_strcmp(head->key, "HOME"))
            break;
        head = head->next;
    }
	if (!head)
	{
		ft_putstr_fd(2, "minishell: cd: HOME not set\n");
		return 1;
	}

	if (chdir(head->value) < 0)
	{
		perror("minishell");
		return 1;//exit	
	}
	return (0);
}

int	cd_2(t_env *env)
{
	t_env *head;

	head = env;
	while (head)
    {
        if (!ft_strcmp(head->key, "OLDPWD"))
            break;
            head = head->next;
    }
	if (!head)
	{
		ft_putstr_fd(2, "minishell: cd: OLDPWD not set\n");
		return 1;
	}
    if (chdir(head->value) < 0)
	{
		perror("minishell");
		return 1;//exit	
	}
	printf("%s\n", head->value);
	return (0);
}

int	unset_parsing(char *str)
{
	if (!ft_isalpha(*str) && *str != '_')
		return (1);
	str++;
	while (*str)
	{
		if (*str != '_' && !ft_isalnum(*str))
			return (1);
		str++;
	}
	return (0);
}