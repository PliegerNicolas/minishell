/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_command_execution.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 20:34:41 by nicolas           #+#    #+#             */
/*   Updated: 2023/04/11 22:01:04 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	open_file(const char *path, const enum e_redir_type redir_type)
{
	int	fd;

	if (!path || !redir_type)
		return (-1);
	if (redir_type == to_file)
		fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir_type == append_to_file)
		fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(path, O_RDONLY, 0644);
	if (fd == -1)
		return (perror("open"), -1);
	return (fd);
}

t_bool	stdin_redirection(t_lexer *lexer, int *previous_fd)
{
	int			fd;

	if (!lexer)
		return (FALSE);
	if (lexer->redir_path[0] && (lexer->redir_type[0] == from_file
			|| lexer->redir_type[0] == heredoc))
	{
		fd = open_file(lexer->redir_path[0], lexer->redir_type[0]);
		if (fd == -1)
			exit(TRUE);
		if (dup2(fd, STDIN_FILENO) == -1)
			return (close(fd), TRUE);
		close(fd);
	}
	else if (*previous_fd)
		if (dup2(*previous_fd, STDIN_FILENO) == -1)
			return (TRUE);
	if (*previous_fd)
	{
		close(*previous_fd);
		*previous_fd = -1;
	}
	return (FALSE);
}

t_bool	stdout_redirection(t_lexer *lexer, int *pipefds)
{
	int	fd;

	if (lexer->redir_path[1] && (lexer->redir_type[1] == to_file
			|| lexer->redir_type[1] == append_to_file))
	{
		fd = open_file(lexer->redir_path[1], lexer->redir_type[1]);
		if (fd == -1)
			return (TRUE);
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (close(fd), TRUE);
		close(fd);
	}
	else if (lexer->next)
	{
		if (dup2(pipefds[1], STDOUT_FILENO) == -1)
			return (TRUE);
		close(pipefds[1]);
	}
	return (FALSE);
}

t_bool	external_execution_child(t_lexer *lexer, int *pipefds,
	int *previous_fd, char ***envp)
{
	if (stdin_redirection(lexer, previous_fd))
		return (TRUE);
	if (stdout_redirection(lexer, pipefds))
		return (TRUE);
	if (execve(lexer->exec, lexer->args, *envp) == -1)
		return (perror("execve"), TRUE);
	return (FALSE);
}

t_bool	external_execution(t_lexer *lexer, int *previous_fd, char ***envp)
{
	pid_t	pid;
	int		pipefds[2];
	t_bool	status;

	if (!lexer)
		return (FALSE);
	if (pipe(pipefds) == -1)
		return (perror("pipe"), close_fds(pipefds, previous_fd), TRUE);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), close_fds(pipefds, previous_fd), TRUE);
	else if (pid == 0)
	{
		status = external_execution_child(lexer, pipefds, previous_fd, envp);
		close_fds(pipefds, previous_fd);
		exit (status);
	}
	else
	{
		waitpid(pid, NULL, 0);
		if (*previous_fd)
			close(*previous_fd);
		*previous_fd = pipefds[0];
		close(pipefds[1]);
	}
	return (FALSE);
}
