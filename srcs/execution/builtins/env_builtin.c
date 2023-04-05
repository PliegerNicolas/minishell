/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 04:03:22 by nicolas           #+#    #+#             */
/*   Updated: 2023/04/05 22:32:57 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_bool	env_builtin(t_lexer *lexer, char ***envp)
{
	size_t	i;

	if (!envp)
		return (g_status = command_invoked_cannot_execute, TRUE);
	if (lexer->options)
		return (g_status = misuse_of_shell_builtins, TRUE);
	if (lexer->args && *(lexer->args + 1))
		return (g_status = misuse_of_shell_builtins, TRUE);
	i = 0;
	while ((*envp)[i])
		ft_putendl_fd((*envp)[i++], STDOUT);
	return (FALSE);
}
