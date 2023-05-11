/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirection_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 01:49:13 by nicolas           #+#    #+#             */
/*   Updated: 2023/05/11 22:03:08 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_bool	set_redir_path(char *pathname, t_lexer *lexer, int slot)
{
	int				fd;

	if (!pathname)
		return (TRUE);
	if (lexer->redir_path[slot])
	{
		if (access(lexer->redir_path[slot], F_OK) == 0
			&& access(lexer->redir_path[slot], W_OK) == -1)
		{
			if (!lexer->err)
				perror("access");
			lexer->err = TRUE;
		}
		else
		{
			fd = open_file(lexer, lexer->redir_path[slot],
					lexer->redir_type[slot]);
			if (fd == -1)
				return (perror("open"), TRUE);
			close(fd);
		}
		free(lexer->redir_path[slot]);
	}
	lexer->redir_path[slot] = pathname;
	return (FALSE);
}
