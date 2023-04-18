/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 20:36:38 by nicolas           #+#    #+#             */
/*   Updated: 2023/04/18 17:06:45 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void	clear_stdin(int *prev_fd)
{
	if (*prev_fd == -1)
		return ;
	close(*prev_fd);
	*prev_fd = -1;
}

static t_bool	stdout_redirection(t_lexer *lexer)
{
	int	fd;

	if (!lexer)
		return (FALSE);
	if (lexer->redir_path[1] && (lexer->redir_type[1] == to_file
			|| lexer->redir_type[1] == append_to_file))
		fd = open_file(lexer->redir_path[1], lexer->redir_type[1]);
	else
		fd = open(".tmp_builtin", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (perror("open"), TRUE);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (perror("dup2"), close(fd), TRUE);
	close(fd);
	return (FALSE);
}

static t_bool	set_prev_fd(t_lexer *lexer, int *prev_fd)
{
	if (!lexer)
		return (FALSE);
	if (lexer->redir_path[1] && (lexer->redir_type[1] == to_file
			|| lexer->redir_type[1] == append_to_file))
	{
		if (!lexer->next)
			return (FALSE);
		*prev_fd = open(lexer->redir_path[1], O_RDONLY);
	}
	else
		*prev_fd = open(".tmp_builtin", O_RDONLY, 0644);
	if (*prev_fd == -1)
		return (perror("open"), TRUE);
	return (FALSE);
}

static t_bool	execute_builtin(t_lexer *lexer, char ***envp)
{
	t_bool	status;

	if (!lexer)
		return (FALSE);
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

t_bool	builtin_execution(t_lexer *lexer, int *prev_fd, char ***envp)
{
	int	stdout_cpy;

	if (!lexer)
		return (FALSE);
	clear_stdin(prev_fd);
	stdout_cpy = dup(STDOUT_FILENO);
	if (stdout_cpy == -1)
		return (TRUE);
	if (stdout_redirection(lexer) == -1)
		return (close(stdout_cpy), TRUE);
	// output function
	//(void)envp;
	//printf("%s\n", lexer->exec);
	execute_builtin(lexer, envp);
	//
	if (dup2(stdout_cpy, STDOUT_FILENO) == -1)
		return (perror("dup2"), close(stdout_cpy), TRUE);
	close(stdout_cpy);
	if (set_prev_fd(lexer, prev_fd))
		return (TRUE);
	unlink(".tmp_builtin");
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
