/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:48:59 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/31 17:56:55 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_bool	set_redirection(const char *str, t_lexer *lexer, t_bool *prev_is_redir)
{
	(void)str;
	(void)lexer;
	if (*prev_is_redir)
	{
		printf("set_redirection via *prev_is_redir\n");
		*prev_is_redir = FALSE;
	}
	else
	{
		printf("set_redirection\n");
		*prev_is_redir = TRUE;
	}
	return (FALSE);
}
