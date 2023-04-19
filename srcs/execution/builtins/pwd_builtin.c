/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 18:59:52 by nicolas           #+#    #+#             */
/*   Updated: 2023/04/19 15:47:18 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_bool	pwd_builtin(t_lexer *lexer)
{
	char	cwd[1024];

	if (!lexer)
		return (FALSE);
	if (ft_strarrlen((const char **)lexer->args) > 1)
	{
		errno = E2BIG;
		return (perror("pwd"), g_status = misuse_of_shell_builtins, FALSE);
	}
	if (getcwd(cwd, sizeof(cwd)))
		ft_putendl_fd(cwd, STDOUT);
	else
		return (g_status = command_invoked_cannot_execute, TRUE);
	return (g_status = success, FALSE);
}
