/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 02:22:35 by isidki            #+#    #+#             */
/*   Updated: 2023/08/19 01:55:36 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_glb	g_glb;

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char	*input;
	t_cmd	*cmd;
	char *test;

	test = malloc(1);
	if (!test)
		exit(1);
	cmd = malloc(sizeof(t_cmd));
	g_glb.exit_status = 0;
	g_glb.dqu = 0;
	g_glb.opn_fls = 0;
	if (env && env[0])
	{
		cmd->env = env;
		g_glb.env = variable_environnement(cmd);
	}
	// else
	// {
	// 	envp = variable_environnement(NULL);//HERE
	// }
	while (1)
	{
		rl_catch_signals = 0;
		ft_signal();
		input = readline("minishell$ ");
		if (!input)
		{
			printf("exit\n");
			exit(g_glb.exit_status);
		}
		if (ft_isspace(input) || !ft_strcmp(input, ""))
		{
			free(input);
			continue ;
		}
		if (input)
			add_history(input);
		cmd = parsing(input, env);
		if (cmd == NULL)
			continue;
		t_env *head;

		head = g_glb.env;
		while (head)
		{
			printf("--->%s=%s\n", head->key, head->value);
			head = head->next;
		}
		redirection(cmd);
		// if (!cmd) 
		// 	break ;
		if (!g_glb.opn_fls)
			g_glb.exit_status = 0; // should rather be done at (exit and echo) in execution
	}
	ft_lstclear_cmd(&cmd);
	clear_history();
	return (0);
}
