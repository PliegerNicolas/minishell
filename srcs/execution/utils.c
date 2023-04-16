/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 19:27:19 by nicolas           #+#    #+#             */
/*   Updated: 2023/04/16 23:08:38 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	put_fd(int fd)
{
	char		buffer[BUFFER_SIZE];
	ssize_t		written_bytes;
	ssize_t		read_bytes;
	ssize_t		hold_bytes;

	read_bytes = 1;
	while (read_bytes > 0)
	{
		read_bytes = read(fd, buffer, sizeof(buffer));
		written_bytes = 0;
		while (written_bytes < read_bytes)
		{
			hold_bytes = write(STDOUT, buffer + written_bytes,
					read_bytes - written_bytes);
			if (hold_bytes < 0)
			{
				perror("write");
				return ;
			}
			written_bytes += hold_bytes;
		}
		read_bytes = 0;
	}
	if (read_bytes < 0)
		perror("read");
}

int	open_file(const char *path, const enum e_redir_type redir_type)
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

void	close_fds(int *pipefds, int *prev_fd)
{
	if (pipefds[0] != -1)
		close(pipefds[0]);
	if (pipefds[1] != -1)
		close(pipefds[1]);
	if (*prev_fd != -1)
	{
		close(*prev_fd);
		*prev_fd = -1;
	}
}
