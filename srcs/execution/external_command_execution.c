/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_command_execution.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 20:34:41 by nicolas           #+#    #+#             */
/*   Updated: 2023/05/07 15:34:57 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static t_bool	infile_redirection(t_lexer *lexer, int *pipefds, int *prev_fd)
{
	if (lexer->redir_path[0] && (lexer->redir_type[0] == from_file
			|| lexer->redir_type[0] == heredoc))
	{
		close_prev_fd(prev_fd);
		*prev_fd = open_file(lexer->redir_path[0], lexer->redir_type[0]);
		if (*prev_fd == -1)
			return (close_fds(pipefds, prev_fd, TRUE),
				g_status = general_failure, TRUE);
		if (dup2(*prev_fd, STDIN_FILENO) == -1)
			return (perror("dup2"), close_fds(pipefds, prev_fd, TRUE),
				g_status = general_failure, TRUE);
		close_prev_fd(prev_fd);
	}
	if (*prev_fd != -1)
	{
		if (dup2(*prev_fd, STDIN_FILENO) == -1)
			return (perror("dup2"), close_fds(pipefds, prev_fd, TRUE),
				g_status = general_failure, TRUE);
		close_prev_fd(prev_fd);
	}
	return (FALSE);
}

static t_bool	outfile_redirection(t_lexer *lexer, int *pipefds, int *prev_fd)
{
	if (lexer->redir_path[1] && (lexer->redir_type[1] == to_file
			|| lexer->redir_type[1] == append_to_file))
	{
		close(pipefds[1]);
		pipefds[1] = -1;
		pipefds[1] = open_file(lexer->redir_path[1], lexer->redir_type[1]);
		if (pipefds[1] == -1)
			return (close_fds(pipefds, prev_fd, TRUE),
				g_status = general_failure, TRUE);
		if (dup2(pipefds[1], STDOUT_FILENO) == -1)
			return (perror("dup2"), close_fds(pipefds, prev_fd, TRUE),
				g_status = general_failure, TRUE);
	}
	else if (lexer->next)
	{
		if (dup2(pipefds[1], STDOUT_FILENO) == -1)
			return (perror("dup2"), close_fds(pipefds, prev_fd, TRUE),
				g_status = general_failure, TRUE);
	}
	close(pipefds[1]);
	return (FALSE);
}

static t_bool	child(t_lexer *lexer, int *pipefds, int *prev_fd, char ***envp)
{
	close(pipefds[0]);
	if (infile_redirection(lexer, pipefds, prev_fd))
		return (close_fds(pipefds, prev_fd, TRUE), TRUE);
	if (outfile_redirection(lexer, pipefds, prev_fd))
		return (close_fds(pipefds, prev_fd, TRUE), TRUE);
	close_fds(pipefds, prev_fd, FALSE);
	if (execve(lexer->exec, lexer->args, *envp) == -1)
		return (perror(lexer->exec), g_status = command_not_found,
			close_fds(pipefds, prev_fd, TRUE), FALSE);
	return (g_status = success, close_fds(pipefds, prev_fd, TRUE), FALSE);
}

static t_bool	parent(t_lexer *lexer, int *pipefds, int *prev_fd, pid_t pid)
{
	int		status;

	close(pipefds[1]);
	close_prev_fd(prev_fd);
	if (lexer->next)
	{
		if (lexer->redir_path[1] && (lexer->redir_type[1] == to_file
				|| lexer->redir_type[1] == append_to_file))
		{
			close(pipefds[0]);
			pipefds[0] = -1;
			pipefds[0] = open(lexer->redir_path[1], O_RDONLY);
			if (pipefds[0] == -1)
				return (perror("open"), close_fds(pipefds, prev_fd, TRUE),
					g_status = general_failure, TRUE);
		}
		*prev_fd = dup(pipefds[0]);
	}
	else
	{
		waitpid(pid, &status, 0);
		g_status = WEXITSTATUS(status);
	}
	close(pipefds[0]);
	return (FALSE);
}

t_bool	external_execution(t_lexer *lexer, int *prev_fd, char ***envp)
{
	pid_t	pid;
	int		pipefds[2];

	if (pipe(pipefds) == -1)
		return (perror("pipe"), close_fds(pipefds, prev_fd, TRUE),
			g_status = general_failure, TRUE);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), close_fds(pipefds, prev_fd, TRUE),
			g_status = general_failure, TRUE);
	else if (pid == 0)
	{
		(void)child(lexer, pipefds, prev_fd, envp);
		exit(g_status);
	}
	else
		if (parent(lexer, pipefds, prev_fd, pid))
			return (TRUE);
	return (FALSE);
}
