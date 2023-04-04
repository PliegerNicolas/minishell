/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 18:59:52 by nicolas           #+#    #+#             */
/*   Updated: 2023/04/04 19:06:01 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_bool	pwd_builtin(t_lexer *lexer, char **envp)
{
	char	cwd[1024];

	if (!envp)
		return (g_status = command_invoked_cannot_execute, TRUE);
	if (lexer->options)
		return (g_status = misuse_of_shell_builtins, TRUE);
	if (getcwd(cwd, sizeof(cwd)))
		ft_putendl_fd(cwd, STDOUT);
	else
		return (g_status = command_invoked_cannot_execute, TRUE);
	return (FALSE);
}