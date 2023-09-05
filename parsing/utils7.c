/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 03:28:00 by osarsar           #+#    #+#             */
/*   Updated: 2023/09/05 03:30:13 by osarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_dqu(t_lexer *temp, t_lexer *hold, t_token tok)
{
	if (!temp)
	{
		ft_putstr_fd(2, "minishell: syntax error near unclosed quotes\n");
		g_glb.exit_status = 258;
		return (1);
	}
	else if (hold != temp && hold)
		concat_between_qu(hold, temp, tok); //hold is first elm after '\"' and temp is the closing '\"'
	return (0);
}

void	empty_string(t_lexer **l, t_lexer *hold, t_token tok)
{
	ft_free(hold->cmd);
	hold->cmd = ft_strdup("");
	hold->token = tok;
	ft_delete_node(l, hold->prev);
}

void	assign_tok(t_lexer *tmp, t_token *tok)
{
	if (tmp->token == DQU)
		*tok = DQU;
	else if (tmp->token == SQU)
		*tok = SQU;
}

int	ft_check_quotes(t_lexer **l)
{
	t_lexer	*temp;
	t_lexer	*hold;
	t_token	tok;

	temp = *l;
	while (temp)
	{
		tok = temp->token;
		assign_tok(temp, &tok);
		if (tok == SQU || tok == DQU)
		{
			hold = temp->next;
			temp = find_matching_quote(temp, tok);
			if (handle_dqu(temp, hold, tok))
				return (1);
			else if (hold == temp && hold)
				empty_string(l, hold, tok);
		}
		else if (temp->token == SPC && temp->next && temp->next->token == SPC)
			delete_spc(l, temp);
		if (temp)
			temp = temp->next;
	}
	return (0);
}
