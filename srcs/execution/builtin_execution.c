/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 20:36:38 by nicolas           #+#    #+#             */
/*   Updated: 2023/05/08 14:20:19 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static t_bool	execute_builtin(t_commands *commands, t_lexer *lexer,
	char ***envp)
{
	t_bool	status;

	if (!lexer)
		return (FALSE);
	status = FALSE;
	if (ft_strncmp(lexer->exec, "echo", 5) == 0)
		status = echo_builtin(lexer);
	else if (ft_strncmp(lexer->exec, "cd", 3) == 0)
		status = cd_builtin(lexer, envp);
	else if (ft_strncmp(lexer->exec, "pwd", 4) == 0)
		status = pwd_builtin(lexer);
	else if (ft_strncmp(lexer->exec, "export", 7) == 0)
		status = export_builtin(lexer, envp);
	else if (ft_strncmp(lexer->exec, "unset", 6) == 0)
		status = unset_builtin(lexer, envp);
	else if (ft_strncmp(lexer->exec, "env", 4) == 0)
		status = env_builtin(lexer, envp);
	else if (ft_strncmp(lexer->exec, "exit", 5) == 0)
		status = exit_builtin(commands, lexer, envp);
	return (status);
}

static t_bool	outfile_redirection(t_lexer *lexer, int *pipefds, int *prev_fd)
{
	if (lexer->redir_path[1] && (lexer->redir_type[1] == to_file
			|| lexer->redir_type[1] == append_to_file))
	{
		*prev_fd = open_file(lexer->redir_path[1], lexer->redir_type[1]);
		if (*prev_fd == -1)
			return (close_fds(pipefds, prev_fd, TRUE),
				g_status = general_failure, TRUE);
		if (dup2(*prev_fd, STDOUT_FILENO) == -1)
			return (perror("dup2"), close_fds(pipefds, prev_fd, TRUE),
				g_status = general_failure, TRUE);
		close_prev_fd(prev_fd);
	}
	else if (lexer->next)
		if (dup2(pipefds[1], STDOUT_FILENO) == -1)
			return (perror("dup2"), close_fds(pipefds, prev_fd, TRUE),
				g_status = general_failure, TRUE);
	close(pipefds[1]);
	return (FALSE);
}

static t_bool	set_prev_fd(t_lexer *lexer, int *pipefds, int *prev_fd)
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
	if (lexer->next)
		*prev_fd = dup(pipefds[0]);
	close(pipefds[0]);
	return (FALSE);
}

static int	exit_exception(t_commands *commands, t_lexer *lexer, char ***envp)
{
	int		fd;

	if (lexer->redir_path[1] && (lexer->redir_type[1] == to_file
			|| lexer->redir_type[1] == append_to_file))
	{
		fd = open_file(lexer->redir_path[1], lexer->redir_type[1]);
		if (fd == -1)
			return (TRUE);
		close(fd);
	}
	if (lexer->previous || lexer->next)
		return (FALSE);
	else
		(void)execute_builtin(commands, lexer, envp);
	return (FALSE);
}

t_bool	builtin_execution(t_commands *commands, t_lexer *lexer,
	int *prev_fd, char ***envp)
{
	int	pipefds[2];
	int	stdout_cpy;

	close_prev_fd(prev_fd);
	if (lexer->exec && ft_strncmp(lexer->exec, "exit", 5) == 0)
	{
		if (exit_exception(commands, lexer, envp))
			return (TRUE);
		return (FALSE);
	}
	stdout_cpy = dup(STDOUT_FILENO);
	if (pipe(pipefds) == -1)
		return (perror("pipe"), close_fds(NULL, prev_fd, TRUE),
			close(stdout_cpy), g_status = general_failure, TRUE);
	if (outfile_redirection(lexer, pipefds, prev_fd))
		return (close(stdout_cpy), TRUE);
	if (execute_builtin(commands, lexer, envp))
		return (close_fds(pipefds, prev_fd, TRUE), close(stdout_cpy), TRUE);
	if (set_prev_fd(lexer, pipefds, prev_fd))
		return (close(stdout_cpy), TRUE);
	if (dup2(stdout_cpy, STDOUT_FILENO) == -1)
		return (perror("dup2"), close_fds(pipefds, prev_fd, TRUE),
			close(stdout_cpy), g_status = general_failure, TRUE);
	return (close(stdout_cpy), FALSE);
}
