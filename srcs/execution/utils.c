/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 19:27:19 by nicolas           #+#    #+#             */
/*   Updated: 2023/05/11 22:04:03 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	open_file(t_lexer *lexer, const char *path,
	const enum e_redir_type redir_type)
{
	int	fd;

	if (!path || !redir_type)
		return (-1);
	if (redir_type == from_file || redir_type == heredoc)
	{
		if (access(path, F_OK) == -1)
			return (perror("access"), -1);
		fd = open(path, O_RDONLY, 0644);
	}
	else if (redir_type == to_file)
		fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir_type == append_to_file)
		fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		return (-1);
	if (fd == -1)
	{
		if (!lexer->err)
			perror("open");
		lexer->err = TRUE;
		return (-1);
	}
	return (fd);
}

void	close_prev_fd(int *prev_fd)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	*prev_fd = -1;
}

void	close_stds(void)
{
	if (STDIN_FILENO != -1)
		close(STDIN_FILENO);
	if (STDOUT_FILENO != -1)
		close(STDOUT_FILENO);
	if (STDERR_FILENO != -1)
		close(STDERR_FILENO);
}

void	close_fds(int *pipefds, int *prev_fd, t_bool stds)
{
	if (pipefds[0] != -1)
	{
		close(pipefds[0]);
		pipefds[0] = -1;
	}
	if (pipefds[1] != -1)
	{
		close(pipefds[1]);
		pipefds[1] = -1;
	}
	close_prev_fd(prev_fd);
	if (stds)
		close_stds();
}
