/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 18:30:59 by nicolas           #+#    #+#             */
/*   Updated: 2023/04/11 00:49:06 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_bool	is_builtin(const char *str)
{
	if (ft_strncmp(str, "echo", 5) == 0)
		return (TRUE);
	else if (ft_strncmp(str, "cd", 3) == 0)
		return (TRUE);
	else if (ft_strncmp(str, "pwd", 4) == 0)
		return (TRUE);
	else if (ft_strncmp(str, "export", 7) == 0)
		return (TRUE);
	else if (ft_strncmp(str, "unset", 6) == 0)
		return (TRUE);
	else if (ft_strncmp(str, "env", 4) == 0)
		return (TRUE);
	else if (ft_strncmp(str, "exit", 5) == 0)
		return (TRUE);
	return (FALSE);
}

t_bool	execute_builtin(t_lexer *lexer, char ***envp)
{
	t_bool	status;

	status = FALSE;
	if (ft_strncmp(lexer->exec, "echo", 5) == 0)
		status = echo_builtin(lexer, envp);
	else if (ft_strncmp(lexer->exec, "cd", 3) == 0)
		status = cd_builtin(lexer, envp);
	else if (ft_strncmp(lexer->exec, "pwd", 4) == 0)
		status = pwd_builtin(lexer, envp);
	else if (ft_strncmp(lexer->exec, "export", 7) == 0)
		status = export_builtin(lexer, envp);
	else if (ft_strncmp(lexer->exec, "unset", 6) == 0)
		status = unset_builtin(lexer, envp);
	else if (ft_strncmp(lexer->exec, "env", 4) == 0)
		status = env_builtin(lexer, envp);
	else if (ft_strncmp(lexer->exec, "exit", 5) == 0)
		status = exit_builtin();
	return (status);
}
