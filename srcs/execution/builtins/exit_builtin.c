/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 23:49:38 by nicolas           #+#    #+#             */
/*   Updated: 2023/04/23 18:07:11 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_bool	exit_builtin(t_lexer *lexer)
{
	size_t	len;

	if (!lexer)
		return (FALSE);
	len = ft_strarrlen((const char **)lexer->args);
	if (len > 1)
	{
		errno = E2BIG;
		return (perror("exit"), g_status = misuse_of_shell_builtins, TRUE);
	}
	g_status = exit_program;
	return (TRUE);
}
