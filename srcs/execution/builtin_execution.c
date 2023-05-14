/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 20:36:38 by nicolas           #+#    #+#             */
/*   Updated: 2023/05/14 15:35:35 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static t_bool	infile_redirection(t_lexer *lexer, int *prev_fd)
{
	close_prev_fd(prev_fd);
	if (lexer->err || (lexer->redir_path[0]
			&& access(lexer->redir_path[0], R_OK) == -1))
	{
		if (!lexer->err)
			perror("access");
		lexer->err = TRUE;
		return (TRUE);
	}
	return (FALSE);
}

static t_bool	outfile_redirection(t_lexer *lexer, int *pipefds, int *prev_fd)
{
	if (lexer->err)
		return (g_status = general_failure, FALSE);
	else if (lexer->redir_path[1]
		&& (access(lexer->redir_path[1], W_OK) == -1 && errno != ENOENT))
	{
		perror("access");
		lexer->err = TRUE;
		return (g_status = general_failure, FALSE);
	}
	if (lexer->redir_path[1] && (lexer->redir_type[1] == to_file
			|| lexer->redir_type[1] == append_to_file))
	{
		*prev_fd = open_file(lexer, lexer->redir_path[1], lexer->redir_type[1]);
		if (*prev_fd == -1)
			return (TRUE);
		if (dup2(*prev_fd, STDOUT_FILENO) == -1)
			return (perror("dup2"), TRUE);
		close_prev_fd(prev_fd);
	}
	else if (lexer->next)
	{
		if (dup2(pipefds[1], STDOUT_FILENO) == -1)
			return (perror("dup2"), TRUE);
	}
	return (close_prev_fd(&pipefds[1]), FALSE);
}

static t_bool	set_prev_fd(t_lexer *lexer, int *pipefds, int *prev_fd)
{
	int		fd;

	if (lexer->next)
	{
		if (lexer->redir_path[1] && (lexer->redir_type[1] == to_file
				|| lexer->redir_type[1] == append_to_file))
		{
			close_fds(pipefds, prev_fd, FALSE);
			fd = open(lexer->redir_path[1], O_RDONLY);
			if (fd == -1)
				return (TRUE); // test
			*prev_fd = fd;
		}
		else
		{
			fd = dup(pipefds[0]);
			close_fds(pipefds, prev_fd, FALSE);
			*prev_fd = fd;
		}
	}
	close_prev_fd(&pipefds[0]);
	return (FALSE);
}

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

t_bool	builtin_execution(t_commands *commands, t_lexer *lexer,
	int *prev_fd, char ***envp)
{
	int		pipefds[2];
	int		stdout_cpy;

	if (infile_redirection(lexer, prev_fd))
		return (g_status = general_failure, FALSE);
	if (pipe(pipefds) == -1)
		return (close_stds(), g_status = general_failure, TRUE);
	stdout_cpy = dup(STDOUT_FILENO);
	if (outfile_redirection(lexer, pipefds, prev_fd))
		return (close_fds(pipefds, prev_fd, TRUE), close(stdout_cpy),
			g_status = general_failure, TRUE);
	if (lexer->err)
		return (close_fds(pipefds, prev_fd, FALSE), close(stdout_cpy),
			g_status = general_failure, FALSE);
	if (execute_builtin(commands, lexer, envp))
		return (close_fds(pipefds, prev_fd, TRUE), close(stdout_cpy), TRUE);
	if (lexer->next || lexer->redir_path[1])
		if (dup2(stdout_cpy, STDOUT_FILENO) == -1)
			return (close_fds(pipefds, prev_fd, TRUE), close(stdout_cpy),
				g_status = general_failure, TRUE);
	close(stdout_cpy);
	if (set_prev_fd(lexer, pipefds, prev_fd))
		return (g_status = general_failure, TRUE);
	return (FALSE);
}
