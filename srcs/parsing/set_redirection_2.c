/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirection_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 01:49:13 by nicolas           #+#    #+#             */
/*   Updated: 2023/06/19 03:29:45 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_bool	set_redir_path(char *pathname, t_lexer *lexer, int slot)
{
	if (!pathname)
		return (TRUE);
	free(lexer->redir_path[slot]);
	lexer->redir_path[slot] = pathname;
	return (FALSE);
}

t_bool	overwrite_redirection(t_lexer *lexer)
{
	int		fd;

	if (lexer->redir_type[1] != to_file)
		return (FALSE);
	if (!lexer->redir_path[1])
		return (TRUE);
	if (access(lexer->redir_path[1], F_OK) == 0
		&& access(lexer->redir_path[1], W_OK) == -1)
	{
		if (!lexer->err)
			perror("access");
		lexer->err = TRUE;
	}
	else
	{
		fd = open_file(lexer, lexer->redir_path[1], lexer->redir_type[1]);
		if (fd == -1)
			return (perror("open"), TRUE);
		close(fd);
	}
	return (FALSE);
}
