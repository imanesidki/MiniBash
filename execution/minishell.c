/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:11:58 by osarsar           #+#    #+#             */
/*   Updated: 2023/08/19 20:11:16 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle(int sig)
{
	if (sig == SIGQUIT)
		printf("\\Quit\n");
	if (sig == SIGINT)
	{
		rl_catch_signals = 0;
		return ;
	}
}

int	redirection(t_cmd *data)
{
	int	in;
	int	out;
	int	fd[2];
	int	pid;

	in = dup(0);
	out = dup(1);
	pid = -1;
	signal(SIGINT, handle);
	signal(SIGQUIT, handle);
	if (data->next)
	{
		while (data->next)
		{
			if (data->fd[0] == -1 || data->fd[1] == -1)
			{
				data = data->next;
				continue;
			}
			pipe(fd);
			pid = fork();
			if (pid == 0)
			{
				close(fd[0]);
				dup2(fd[1], 1);
				close(fd[1]);
				ft_process(data, fd);
			}
			close(fd[1]);
			dup2(fd[0], 0);
			close(fd[0]);
			data = data->next;
		}
		if (data->fd[0] == -1 || data->fd[1] == -1 )
			return (dup2(in, 0), dup2(out, 1), 0);
		pid = fork();
		if (pid == 0)
		{
			if (data->fd[1] != -2)
				dup2(data->fd[1], 1);
			if (data->fd[0] != -2)
				dup2(data->fd[0], 0);
			if (!is_builting(data))
				return (execution(&data), exit(g_glb.exit_status), 0);
			ft_execve_valid_path(data);
		}
	}
	else
	{
		if (data->fd[0] == -1 || data->fd[1] == -1)
			return(dup2(in, 0), dup2(out, 1), 0);		
		if (data->fd[1] != -2)
			dup2(data->fd[1], 1);
		if (data->fd[0] != -2)
			dup2(data->fd[0], 0);
		if (!is_builting(data))
		{
			((execution(&data),dup2(in, 0), dup2(out,1)));
			return(1);
		}
		else
		{
			pid = fork();
			if (pid == 0)
				ft_execve_valid_path(data);
		}
	}
	dup2(in, 0);
	dup2(out, 1);	
	while (wait(&pid) > 0);
	return(0);
}

t_env	*lstcmp()
{
	char	*tmp_key;
	char	*tmp_value;
	char	*tmp_line;
	t_env	*head;
	t_env	*head_n;
	t_env	*dup_export = NULL;

	dup_export = duplicate_env();
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
			printf("declare -x %s\n", head->key);
		}
		else
			printf("declare -x %s=\"%s\"\n", head->key, head->value);
		head = head->next;
	}
	return (head);
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
	return (0);
}

int	check_error(char *key, t_cmd *head)
{
	if (!key)
	{
		printf("minishell: export: `%s': not a valid identifier\n", *head->cmd);
		return(-1);
	}
	if (check_key(key) == -1)
	{
		printf("minishell: export: `%s': not a valid identifier\n", *head->cmd);
		return(-1);
	}
	return (0);
}

int is_builting(t_cmd *data)
{
	if (!data->cmd || !data->cmd[0] || !data)
		return (1);
	if (!ft_strcmp(*data->cmd, "echo") || !ft_strcmp(*data->cmd, "cd") ||
	!ft_strcmp(*data->cmd, "env") || !ft_strcmp(*data->cmd, "export") ||
	!ft_strcmp(*data->cmd, "unset") || !ft_strcmp(*data->cmd, "exit") ||
	!ft_strcmp(*data->cmd, "pwd"))
		return (0);
	return (1);
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