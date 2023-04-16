/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 20:36:38 by nicolas           #+#    #+#             */
/*   Updated: 2023/04/16 18:23:17 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void	stdin_redirection(int *prev_fd)
{
	if (*prev_fd)
	{
		close(*prev_fd);
		*prev_fd = -1;
	}
}

static t_bool	stdout_redirection(t_lexer *lexer, int *pipefds, int *prev_fd)
{
	int		fd;

	if (!lexer)
		return (FALSE);
	if (lexer->redir_path[1] && (lexer->redir_type[1] == to_file
			|| lexer->redir_type[1] == append_to_file))
	{
		fd = open_file(lexer->redir_path[1], lexer->redir_type[1]);
		if (fd == -1)
			return (close_fds(pipefds, prev_fd), TRUE);
		if (dup2(fd, pipefds[1]) == -1)
			return (close(fd), close_fds(pipefds, prev_fd), TRUE);
		close(fd);
		if (dup2(pipefds[1], STDOUT_FILENO) == -1)
			return (close_fds(pipefds, prev_fd), TRUE);
		close(pipefds[1]);
	}
	else if (lexer->next)
	{
		if (dup2(pipefds[1], STDOUT_FILENO) == -1)
			return (close_fds(pipefds, prev_fd), TRUE);
		close(pipefds[1]);
	}
	return (FALSE);
}

t_bool	builtin_execution(t_lexer *lexer, int *prev_fd, char ***envp)
{
	int	pipefds[2];

	if (!lexer)
		return (FALSE);
	if (pipe(pipefds) == -1)
		return (perror("pipe"), close_fds(pipefds, prev_fd), TRUE);
	stdin_redirection(prev_fd);
	if (stdout_redirection(lexer, pipefds, prev_fd))
		return (close_fds(pipefds, prev_fd), TRUE);
	(void)envp;
	printf("%s\n", lexer->exec); // temp
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
