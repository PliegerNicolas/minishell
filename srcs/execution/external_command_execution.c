/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_command_execution.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 20:34:41 by nicolas           #+#    #+#             */
/*   Updated: 2023/04/26 18:41:03 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

// prev_fd = -1
// rien stdin
// pipefds open 0 et 1
// rien
static t_bool	stdin_redirection(t_lexer *lexer, int *prev_fd)
{
	int	fd;

	if (!lexer)
		return (FALSE);
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
	else if (*prev_fd != -1)
	{
		if (dup2(*prev_fd, STDIN_FILENO) == -1)
			return (perror("dup2"), close(*prev_fd), TRUE);
	}
	else
		close(STDIN_FILENO);
	if (*prev_fd != -1)
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
	else
		close(pipefds[1]);
	return (FALSE);
}

static void	child(t_lexer *lexer, int *pipefds, int *prev_fd, char ***envp)
{
	close(pipefds[0]);
	if (stdin_redirection(lexer, prev_fd) || stdout_redirection(lexer, pipefds))
	{
		close_fds(pipefds, prev_fd);
		close_stds();
		free_lexer(lexer);
		free_envp(*envp);
		exit(general_failure);
	}
	if (execve(lexer->exec, lexer->args, *envp) == -1)
	{
		perror("execve");
		close_fds(pipefds, prev_fd);
		close_stds();
		free_lexer(lexer);
		free_envp(*envp);
		exit(command_not_found);
	}
	close_fds(pipefds, prev_fd);
	close_stds();
	free_lexer(lexer);
	free_envp(*envp);
	exit(success);
}

static t_bool	parent(t_lexer *lexer, int *pipefds, int *prev_fd, pid_t pid)
{
	int	status;

	close(pipefds[1]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_status = WEXITSTATUS(status);
	if (*prev_fd != -1)
		close(*prev_fd);
	if (lexer->next && lexer->redir_path[1] && (lexer->redir_type[1] == to_file
			|| lexer->redir_type[1] == append_to_file))
	{
		*prev_fd = open(lexer->redir_path[1], O_RDONLY);
		if (*prev_fd == -1)
			return (perror("open"), close_fds(pipefds, prev_fd), TRUE);
	}
	else if (lexer->next)
	{
		*prev_fd = dup(pipefds[0]);
		if (*prev_fd == -1)
			return (g_status = general_failure,
				close_fds(pipefds, prev_fd), TRUE);
	}
	if (g_status == general_failure)
		return (close_fds(pipefds, prev_fd), TRUE);
	return (close(pipefds[0]), FALSE);
}

t_bool	external_execution(t_lexer *lexer, int *prev_fd, char ***envp)
{
	pid_t	pid;
	int		pipefds[2];

	if (!lexer)
		return (FALSE);
	if (pipe(pipefds) == -1)
		return (g_status = general_failure,
			perror("pipe"), close_fds(pipefds, prev_fd), TRUE);
	pid = fork();
	if (pid == -1)
		return (g_status = general_failure,
			perror("fork"), close_fds(pipefds, prev_fd), TRUE);
	else if (pid == 0)
		child(lexer, pipefds, prev_fd, envp);
	else
		if (parent(lexer, pipefds, prev_fd, pid))
			return (g_status = general_failure, TRUE);
	return (FALSE);
}
