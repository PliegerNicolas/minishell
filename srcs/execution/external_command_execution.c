/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_command_execution.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 20:34:41 by nicolas           #+#    #+#             */
/*   Updated: 2023/05/06 19:14:57 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_bool	external_execution(t_lexer *lexer, int *prev_fd, char ***envp)
{
	pid_t	pid;
	int		pipefds[2];

	// Pipe
	if (pipe(pipefds) == -1)
		return (perror("pipe"), g_status = general_failure, TRUE); // correct

	// Fork
	pid = fork();
	if (pid == -1)
		return (perror("fork"), g_status = general_failure, TRUE); // correct
	else if (pid == 0)
	{
		// Child
		close(pipefds[0]);

		// if infile redirection
		if (lexer->redir_path[0] && (lexer->redir_type[0] == from_file
				|| lexer->redir_type[0] == heredoc))
		{
			if (*prev_fd != -1)
				close(*prev_fd);
			*prev_fd = open_file(lexer->redir_path[0], lexer->redir_type[0]);
			if (*prev_fd == -1)
			{
				g_status = general_failure;
				exit(1);
			}
			if (dup2(*prev_fd, STDIN_FILENO) == -1)
			{
				perror("dup2");
				g_status = general_failure;
				exit(1);
			}
			close(*prev_fd);
			*prev_fd = -1;
		}

		// Redirect *prev_fd to stdin
		if (*prev_fd != -1)
		{
			if (dup2(*prev_fd, STDIN_FILENO) == -1)
			{
				perror("dup2");
				g_status = general_failure;
				exit(1);
			}
			close(*prev_fd);
			*prev_fd = -1;
		}

		// if outfile redirection
		if (lexer->redir_path[1] && (lexer->redir_type[1] == to_file
				|| lexer->redir_type[1] == append_to_file))
		{
			close(pipefds[1]);
			pipefds[1] = -1;
			pipefds[1] = open_file(lexer->redir_path[1], lexer->redir_type[1]);
			if (pipefds[1] == -1)
			{
				g_status = general_failure;
				exit(1);
			}
			if (dup2(pipefds[1], STDOUT_FILENO) == -1)
			{
				perror("dup2");
				g_status = general_failure;
				exit(1);
			}
			close(pipefds[1]);
		}
		else if (lexer->next)
		{
			// redirect output to stdout
			if (dup2(pipefds[1], STDOUT_FILENO) == -1)
			{
				perror("dup2");
				g_status = general_failure;
				exit(1);
			}
			close(pipefds[1]);
		}
		else
			close(pipefds[1]);
		
		// Execution
		execve(lexer->exec, lexer->args, *envp);
		perror(lexer->exec);

		exit(0);
	}
	else
	{
		// Parent
		close(pipefds[1]);

		if  (*prev_fd != -1)
		{
			close(*prev_fd);
			*prev_fd = -1;
		}


		// if outfile redirection
		if (lexer->next)
		{
			if (lexer->redir_path[1] && (lexer->redir_type[1] == to_file
					|| lexer->redir_type[1] == append_to_file))
			{
				close(pipefds[0]);
				pipefds[0] = -1;
				pipefds[0] = open(lexer->redir_path[1], O_RDONLY);
				if (pipefds[0] == -1)
					return (perror("open"), g_status = general_failure, TRUE); // correct
			}
			*prev_fd = dup(pipefds[0]);
		}
		else
			if  (waitpid(pid, NULL, 0) == -1)
				return (perror("waitpid"), g_status = general_failure, TRUE); // correct
		close(pipefds[0]);

		return (g_status = success, FALSE);
	}
}
/*
t_bool	external_execution(t_lexer *lexer, char ***envp)
{
	pid_t	pid;
	int		pipefds[2];
	
	// Pipe
	if (pipe(pipefds) == -1)
		return (perror("pipe"), g_status = general_failure, TRUE); // correct

	// Fork
	pid = fork();
	if (pid == -1)
		return (perror("fork"), g_status = general_failure, TRUE); // correct
	else if (pid == 0)
	{
		// Child
		close(pipefds[0]);

		// redirect output
		if (lexer->next)
		{
			if (dup2(pipefds[1], STDOUT_FILENO) == -1)
				return (perror("dup2"), g_status = general_failure, TRUE); // correct
			close(pipefds[1]);
		}
		else
			close(pipefds[1]);

		// execution
		execve(lexer->exec, lexer->args, *envp);
		perror(lexer->exec);

		// exit
		exit(0);
	}
	else
	{
		// Parent
		close(pipefds[1]);

		if (lexer->next)
		{
			if (dup2(pipefds[0], STDIN_FILENO) == -1)
				return (perror("dup2"), g_status = general_failure, TRUE); // correct
			close(pipefds[0]);
		}
		else
		{
			close(pipefds[0]);
			if (waitpid(pid, NULL, 0) == -1)
				return (perror("waitpid"), g_status = general_failure, TRUE); // correct
		}
		return (g_status = success, FALSE);
	}
}
*/

/*
t_bool	external_execution(t_lexer *lexer, int *prev_fd, char ***envp)
{
	pid_t	pid;
	int		pipefds[2];

	// Pipe
	if (pipe(pipefds) == -1)
		return (perror("pipe"), g_status = general_failure, TRUE); // correct

	// Fork
	pid = fork();
	if (pid == -1)
		return (perror("fork"), g_status = general_failure, TRUE); // correct
	else if (pid == 0)
	{
		// Child
		close(pipefds[0]);

		// Redirect previous output to command.
		if (*prev_fd != -1)
		{
			if (dup2(*prev_fd, STDIN_FILENO) == -1)
				return (perror("dup2"), g_status = general_failure, TRUE); // correct
			close(*prev_fd);
		}

		// Redirect output to parent if next command is expected.
		if (lexer->next)
		{
			if (dup2(pipefds[1], STDOUT_FILENO) == -1)
				return (perror("dup2"), g_status = general_failure, TRUE); // correct
			close(pipefds[1]);
		}
		else
			close(pipefds[1]);

		// Execution
		execve(lexer->exec, lexer->args, *envp);
		perror(lexer->exec);
		exit (EXIT_FAILURE); // correct
	}
	else
	{
		// Parent
		close(pipefds[1]);

		if (lexer->next)
		{
			if (*prev_fd != -1)
				close(*prev_fd);
			*prev_fd = pipefds[0];
			//if (dup2(pipefds[0], STDIN_FILENO) == -1)
			//	return (perror("dup2"), g_status = general_failure, TRUE); // correct
			//close(pipefds[0]);
		}
		else
		{
			close(pipefds[0]);
			if (waitpid(pid, NULL, 0) == -1)
				return (perror("waitpid"), g_status = general_failure, TRUE); // correct
		}
		return (g_status = success, FALSE);
	}
}
*/
/*
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
*/
