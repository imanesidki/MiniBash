/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 02:22:35 by isidki            #+#    #+#             */
/*   Updated: 2023/09/06 14:47:47 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_level(void)
{
	t_env	*head;
	int		i;

	head = g_glb.env;
	while (head)
	{
		if (!ft_strcmp(head->key, "SHLVL"))
		{
			i = ft_atoi(head->value);
			i++;
			if (i > 999 || i < 0)
				head->value = ft_itoa(2);
			else
				head->value = ft_itoa(i);
			break ;
		}
		head = head->next;
	}
}

int	main_init(char **env, int ac, char **av)
{
	char	*test;

	if (ac != 1)
	{
		ft_putstr_fd(2, "minishell: No such file or directory\n");
		return (-1);
	}
	(void)av;
	test = malloc(1);
	if (!test)
		exit(1);
	free(test);
	g_glb.exit_status = 0;
	g_glb.dqu = 0;
	g_glb.opn_fls = 0;
	if (env && env[0])
		variable_environnement(env);
	shell_level();
	return (0);
}

int	protection_input(char *input)
{
	if (!input)
	{
		printf("exit\n");
		exit(g_glb.exit_status);
	}
	if (ft_isspace(input) || !ft_strcmp(input, ""))
		return (free(input), 1);
	return (0);
}

void	clear_env(void)
{
	while (g_glb.env)
	{
		free(g_glb.env);
		g_glb.env = g_glb.env->next;
	}
}
void	ft_close_fd()
{
	int fd;

	fd = 3;
	while (fd <= 20)
	{
		if (fstat(fd, NULL) == -1)
		{
			close(fd);
		}
		fd++;
	}
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_cmd	*cmd;

	if (main_init(env, ac, av) == -1)
		return (1);
	while (1)
	{
		ft_signal();
		input = readline("minishell$ ");
		if (protection_input(input))
			continue ;
		add_history(input);
		cmd = parsing(input);
		if (cmd == NULL)
		{
			ft_close_fd();
			continue ;
		}
		split_ls(&cmd);
		if (cmd->cmd && cmd->cmd[0])
			execution_and_redirection(cmd);
		else
			close(cmd->fd[0]);
		ft_lstclear_cmd(&cmd);
	}
	return (clear_history(), clear_env(), 0);
}
