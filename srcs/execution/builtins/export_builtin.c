/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 15:14:22 by nicolas           #+#    #+#             */
/*   Updated: 2023/04/05 15:48:13 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_bool	export(char *arg, char **envp)
{
	(void)arg;
	(void)envp;
	return (FALSE);
}

t_bool	export_builtin(t_lexer *lexer, char **envp)
{
	if (lexer->options)
		return (perror_unexpected_option(),
			g_status = misuse_of_shell_builtins, TRUE);
	if (lexer && *(lexer->args + 2))
		return (perror_too_many_arguments(), g_status = general_failure, TRUE);
	if (export(*(lexer->args + 1), envp))
		return (TRUE);
	return (FALSE);
}
