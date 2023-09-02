/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 02:22:35 by isidki            #+#    #+#             */
/*   Updated: 2023/09/02 03:37:43 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main_init(char **env, int ac)
{
	char	*test;

	if (ac != 1)
	{
		ft_putstr_fd(2, "minishell: No such file or directory\n");
		return (-1);
	}
	test = malloc(1);
	if (!test)
		exit(1);
	free(test);
	g_glb.exit_status = 0;
	g_glb.dqu = 0;
	g_glb.opn_fls = 0;
	if (env && env[0])
		variable_environnement(env);
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
void	clear_env()
{
	while (g_glb.env)
	{
		free(g_glb.env);
		g_glb.env = g_glb.env->next;
	}
}

int	main(int ac, char **av, char **env)//exit after ft_malloc in parsing and execution
{
	char	*input;
	t_cmd	*cmd;

	(void) av;
	if (main_init(env, ac) == -1)
		return (1);
	while (1)
	{
		rl_catch_signals = 0;
		ft_signal();
		input = readline("minishell$ ");
		if (protection_input(input))
			continue ;
		if (input)
			add_history(input);
		cmd = parsing(input);
		if (cmd == NULL)
			continue ;
		execution_and_redirection(cmd);
		// if (!g_glb.opn_fls)
		// 	g_glb.exit_status = 0; // should rather be done at (exit and echo) in execution
		ft_lstclear_cmd(&cmd);
	}
	clear_history();
	clear_env();
	return (0);
}
