/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 20:36:38 by nicolas           #+#    #+#             */
/*   Updated: 2023/04/17 00:26:09 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void	stdin_redirection(int *prev_fd)
{
	if (*prev_fd != -1)
	{
		close(*prev_fd);
		*prev_fd = -1;
	}
}

static t_bool	stdout_redirection(t_lexer *lexer, int *prev_fd)
{
	if (!lexer)
		return (FALSE);
	(void)prev_fd;
	return (FALSE);
}

t_bool	builtin_execution(t_lexer *lexer, int *prev_fd, char ***envp)
{
	if (!lexer)
		return (FALSE);
	stdin_redirection(prev_fd);
	if (stdout_redirection(lexer, prev_fd))
		return (close(*prev_fd), TRUE);
	printf("%s\n", lexer->exec);
	(void)envp;
	return (FALSE);
}
/*
t_bool	builtin_execution(t_lexer *lexer, char ***envp)
{
	t_bool	status;

	if (!lexer)
		return (FALSE);
	printf("%sbuiltin%s\n", RED, WHITE);
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
*/
