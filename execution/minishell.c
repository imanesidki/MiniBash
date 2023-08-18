/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:11:58 by osarsar           #+#    #+#             */
/*   Updated: 2023/08/18 02:49:57 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_process(t_cmd *data, t_env *envp, int fd[2])
{
	// int	pid;

	// pipe(fd);
	(void)fd;

		if (data->fd[0] != -2)
			dup2(data->fd[0], 0);
		if (data->fd[1] != -2)
			dup2(data->fd[1], 1);
		if (!is_builting(data))
		{
			execution(&data, envp);
			exit(0);
		}
		else
			ft_execve_valid_path(data, envp);
	// wait(0);
	// close(fd[1]);
	// dup2(fd[0], 0);
	// close(fd[0]);
}

void	handle(int sig)
{
	if(sig == SIGQUIT)
		printf("\\Quit\n");
	if(sig == SIGINT)
	{
		rl_catch_signals = 0;
		return;
	}
}

void redirection(t_cmd *data, t_env *envp)
{
	int in = dup(0);
	int	out = dup(1);
	int	fd[2];
	int pid = -1;
	signal(SIGINT, handle);
	signal(SIGQUIT, handle);
	if (data->next)
	{
		while (data->next)
		{
			pipe(fd);
			pid = fork();
			if (pid == 0)
			{
				close(fd[0]);
				dup2(fd[1], 1);
				close(fd[1]);
				if (data->fd[1] != -2)
					dup2(data->fd[1], 1);
				if (data->fd[0] != -2)
					dup2(data->fd[0], 0);
				ft_process(data, envp, fd);
			}
			close(fd[1]);
			dup2(fd[0], 0);
			close(fd[0]);
			data = data->next;
		}
		pid = fork();
		if (pid == 0)
		{
			if (data->fd[1] != -2)
				dup2(data->fd[1], 1);
			if (data->fd[0] != -2)
				dup2(data->fd[0], 0);
			if (!is_builting(data))
				return(execution(&data, envp));
				exec_cmd(data, envp);
		}
	}
	else
	{
		if (data->fd[1] != -2)
			dup2(data->fd[1], 1);
		if (data->fd[0] != -2)
			dup2(data->fd[0], 0);
		if (!is_builting(data) )
			return(execution(&data, envp));
		else
		{
			pid = fork();
			if (pid == 0)
				exec_cmd(data, envp);
		}
	}
	dup2(in , 0);
	dup2(out , 1);
	while(wait(&pid) > 0);
}

// void	swap_list()
// {

// }

t_env *lstcmp(t_env *export)
{
	char *tmp_key;
	char *tmp_value;
	char *tmp_line;
	t_env *head;
	t_env *head_n;
	t_env *dup_export;

	dup_export = duplicate_env(export);
	head = dup_export;
	while ((head)->next)
	{
		(head_n) = head->next;
		while (head_n)
		{
			if (ft_strcmp((head)->line, (head_n)->line) > 0)
			{
				tmp_value = (head)->value;
				tmp_key = (head)->key;
				tmp_line = (head)->line;
				(head)->value = (head_n)->value;
				(head)->key = (head_n)->key;
				(head)->line = (head_n)->line;
				(head_n)->value = tmp_value;
				(head_n)->key = tmp_key;
				(head_n)->line = tmp_line;
			}
			(head_n) = (head_n)->next;
		}
		(head) = (head)->next;
	}
	head = dup_export;	
	while (head)
	{
		if (!ft_strcmp(head->line, head->key))
		{
			printf("declare -x %s\n",head->key);
		}
		else
			printf("declare -x %s=\"%s\"\n",head->key, head->value);
		head = head->next;
	}
	return(head);
}

int	check_key(char *key)
{
	while (*key)
	{
		if (*key == '+' && *(key + 1) == '=')
			return (1);
		else if (*key == '+' && *(key + 1) != '=')
			return (-1);
		else if (*key == '=')
			return (2);
		key++;
	}
	return(0);
}

int is_builting(t_cmd *data)
{
	if (!data->cmd || !data->cmd[0] || !data)
		return(1);
	if (!ft_strcmp(*data->cmd, "echo") || !ft_strcmp(*data->cmd, "cd") ||
	!ft_strcmp(*data->cmd, "env") || !ft_strcmp(*data->cmd, "export") ||
	!ft_strcmp(*data->cmd, "unset") || !ft_strcmp(*data->cmd, "exit") ||
	!ft_strcmp(*data->cmd, "pwd"))
		return (0);
	return (1);
}

int	keycmp(t_env **export, t_cmd *head)
{
	t_env	*headexp;
	t_env	*tab;
	char	*key;
	char	*path;
	char	*value;
	int		i;

	headexp = *export;
	value = ft_value(*head->cmd);
	key = ft_substr(*head->cmd, 0, ft_strlen(*head->cmd) - ft_strlen(value));
	if (check_key(key) == -1)
	{
		printf("minishell: export: `%s': not a valid identifier\n", *head->cmd);
		return(-1);
	}
	else if (check_key(key) == 1)
	{
		i = 1;
		key = ft_substr(*head->cmd, 0, ft_strlen(*head->cmd) - ft_strlen(value) - 2);
	}
	else if (check_key(key) == 2)
	{
		i = 2;
		key = ft_substr(*head->cmd, 0, ft_strlen(*head->cmd) - ft_strlen(value) - 1);
	}
	else
	{
		key = *head->cmd;
	}
	path = key;
	while (*path)
	{
		if (!ft_isalpha(*path))
		{
			printf("path = %s\n", path);
			printf("minishell: export: `%s': not a valid identifier\n", *head->cmd);
			return (-1);
		}
		path++;
	}
	while (headexp)
	{
		if (!ft_strcmp(headexp->key, key))
		{
			if (i == 2)    //x=p
			{
				headexp->value = value;
				headexp->line = *head->cmd;
				return (0);
			}
			else if (i == 1)//x+=p
			{
				headexp->value = ft_strjoin(headexp->value, value);
				headexp->line = *head->cmd;
				return (0);
			}
			else
				return (0);
		}
		headexp = headexp->next;
	}
	tab = ft_lstnew_2(*head->cmd, key, value);
	ft_lstadd_back_2(export, tab);
	return (0);
}

// int	main(int ac, char **av, char **envp)
// {
// 	(void)ac;
// 	(void)av;
// 	t_cmd*data;
// 	t_cmd *head;
// 	t_env	*env;
// 	t_env	*export;
// 	int		in;
// 	int		out;

// 	data = malloc(sizeof(t_cmd)); //ft_calloc
// 	data->env = envp;
// 	env = variable_environnement(data);
// 	export = variable_environnement(data);
// 	while (1)
// 	{
// 		// in = dup(0);
// 		// out = dup(1);
// 		data->input = readline("minishell $ ");
// 		if(!data->input)
// 			exit(0);
// 		if (ft_strcmp(data->input, ""))
// 		{
// 			add_history(data->input);
// 			take_cmd(&data);
// 			ft_type(&data);
// 			//redirection(&data);
// 			execution(data, env, export);
// 			// dup2(in, 0);
// 			// dup2(out, 1);
// 		}
// 	}
// }

// int 	len(t_cmd **head)
// {
// 	int		i;
// 	char	*str;

// 	i = 0;
// 	str = (*head)->cmd;
// 	while (str)
// 	{
// 		if (*str == '=')
// 			break;
// 		i++;
// 		str++;
// 	}
// 	return(i);
// }