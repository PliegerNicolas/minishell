/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_command_execution.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 20:34:41 by nicolas           #+#    #+#             */
/*   Updated: 2023/04/15 23:38:55 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static t_bool	stdin_redirection(t_lexer *lexer, int *prev_fd)
{
	int	fd;

	if (!lexer)
		return (FALSE);
	if (lexer->id == 1)
		*prev_fd = STDIN_FILENO;
	if (lexer->redir_path[0] && (lexer->redir_type[0] == from_file
			|| lexer->redir_type[0] == heredoc))
	{
		fd = open_file(lexer->redir_path[0], lexer->redir_type[0]);
		if (fd == -1)
			return (TRUE);
		if (dup2(fd, STDIN_FILENO) == -1)
			return (perror("dup2"), close(fd), TRUE);
		close(fd);
	}
	else if (*prev_fd)
	{
		if (dup2(*prev_fd, STDIN_FILENO) == -1)
			return (perror("dup2"), TRUE);
	}
	if (*prev_fd)
		close(*prev_fd);
	*prev_fd = -1;
	return (FALSE);
}

static t_bool	stdout_redirection(t_lexer *lexer, int *pipefds)
{
	int	fd;

	if (!lexer)
		return (FALSE);
	if (lexer->redir_path[1] && (lexer->redir_type[1] == to_file
			|| lexer->redir_type[1] == append_to_file))
	{
		fd = open_file(lexer->redir_path[1], lexer->redir_type[1]);
		if (fd == -1)
			return (TRUE);
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (perror("dup2"), close(fd), TRUE);
		close(fd);
	}
	else if (lexer->next)
	{
		if (dup2(pipefds[1], STDOUT_FILENO) == -1)
			return (perror("dup2"), TRUE);
		close(pipefds[1]);
	}
	return (FALSE);
}

static void	child(t_lexer *lexer, int *pipefds, int *prev_fd, char ***envp)
{
	close(pipefds[0]);
	if (stdin_redirection(lexer, prev_fd) || stdout_redirection(lexer, pipefds))
	{
		close_fds(pipefds, prev_fd);
		free_lexer(lexer);
		free_envp(*envp);
		exit(TRUE);
	}
	if (execve(lexer->exec, lexer->args, *envp) == -1)
	{
		perror("execve");
		close_fds(pipefds, prev_fd);
		free_lexer(lexer);
		free_envp(*envp);
		exit(TRUE);
	}
	close_fds(pipefds, prev_fd);
	free_lexer(lexer);
	free_envp(*envp);
	exit (FALSE);
}

static t_bool	parent(t_lexer *lexer, int *pipefds, int *prev_fd, pid_t pid)
{
	close(pipefds[1]);
	waitpid(pid, NULL, 0);
	if (!lexer)
		return (FALSE);
	if (lexer->redir_path[1] && (lexer->redir_type[1] == to_file
			|| lexer->redir_type[1] == append_to_file))
	{
		if (*prev_fd)
			close(*prev_fd);
		*prev_fd = open(lexer->redir_path[1], O_RDONLY);
		if (*prev_fd == -1)
			return (perror("open"), close_fds(pipefds, prev_fd), TRUE);
	}
	else
	{
		if (*prev_fd)
			close(*prev_fd);
		*prev_fd = pipefds[0];
	}
	return (FALSE);
}

t_bool	external_execution(t_lexer *lexer, int *prev_fd, char ***envp)
{
	pid_t	pid;
	int		pipefds[2];

	if (!lexer)
		return (FALSE);
	if (pipe(pipefds) == -1)
		return (perror("pipe"), close_fds(pipefds, prev_fd), TRUE);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), close_fds(pipefds, prev_fd), TRUE);
	else if (pid == 0)
		child(lexer, pipefds, prev_fd, envp);
	else
		if (parent(lexer, pipefds, prev_fd, pid))
			return (TRUE);
	return (FALSE);
}

/*
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
		return (close(pipefds[1]), FALSE);
	}
}
*/
