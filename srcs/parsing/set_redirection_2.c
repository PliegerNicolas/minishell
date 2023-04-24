/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirection_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 01:49:13 by nicolas           #+#    #+#             */
/*   Updated: 2023/04/24 15:05:55 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_bool	set_redir_path(char *pathname, t_lexer *lexer, int slot)
{
	if (!pathname)
		return (TRUE);
	if (lexer->redir_path[slot])
		free(lexer->redir_path[slot]);
	lexer->redir_path[slot] = pathname;
	return (FALSE);
}
