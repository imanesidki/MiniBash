/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 03:53:14 by osarsar           #+#    #+#             */
/*   Updated: 2023/09/06 14:29:46 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_glb.sg = 1;
		ioctl(0, TIOCSTI, "\4");
	}
}

void	sig_handl(int sig)
{
	(void)sig;
	if (waitpid(0, NULL, WNOHANG))
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_glb.exit_status = 1;
	}
}

void	ft_signal(void)
{
	rl_catch_signals = 0;
	if (signal(SIGINT, sig_handl) == SIG_ERR
		|| signal(SIGQUIT, SIG_IGN) == SIG_ERR
		|| signal(SIGTSTP, SIG_IGN) == SIG_ERR)
	{
		ft_putstr_fd(2, "signal error\n");
		g_glb.exit_status = 1;
	}
}

int	ft_syntax_error(t_lexer *tmp)
{
	if ((tmp->token == IN || tmp->token == OUT
			|| tmp->token == APPEND || tmp->token == HEREDOC
			|| tmp->token == PIPE) && !(tmp->next))
	{
		ft_putstr_fd(2, "minishell: syntax error ");
		ft_putstr_fd(2, "near unexpected token `newline'\n");
		return (1);
	}
	if (unexpected_tok(tmp))
		return (1);
	if (tmp->token == PIPE && tmp->next && (tmp->next->token == PIPE
			|| (tmp->next->token == SPC && tmp->next->next
				&& tmp->next->next->token == PIPE)))
	{
		ft_putstr_fd(2, "minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	return (0);
}

int	ft_parser(t_lexer **head)
{
	t_lexer	*tmp;

	tmp = *head;
	if (tmp && !tmp->prev && tmp->token == PIPE)
	{
		ft_putstr_fd(2, "minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	while (tmp)
	{
		if (ft_syntax_error(tmp))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
