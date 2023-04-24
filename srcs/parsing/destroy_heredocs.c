/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_heredocs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:35:58 by nicolas           #+#    #+#             */
/*   Updated: 2023/04/24 15:37:03 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	from_commands_destroy_heredocs(t_commands *commands)
{
	while (commands)
	{
		from_lexer_destroy_heredocs(commands->lexer);
		commands = commands->next;
	}
}

void	from_lexer_destroy_heredocs(t_lexer *lexer)
{
	while (lexer)
	{
		if (lexer->redir_type[0] == heredoc && lexer->redir_path[0])
			unlink(lexer->redir_path[0]);
		lexer = lexer->next;
	}
}
