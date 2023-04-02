/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirection_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 01:49:13 by nicolas           #+#    #+#             */
/*   Updated: 2023/04/02 03:33:38 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_bool	set_fd_to_file(const char *pathname, t_lexer *lexer)
{
	int	fd;

	if (lexer->pipefds[1] > 2)
		close(lexer->pipefds[1]);
	fd = access(pathname, F_OK);
	if (fd == -1)
	{
		fd = open(pathname, O_CREAT | O_WRONLY,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		if (fd == -1)
			return (perror_file(), TRUE);
	}
	else
	{
		fd = access(pathname, W_OK);
		if (fd == -1)
			return (perror_file(), TRUE);
		fd = open(pathname, O_WRONLY,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		if (fd == -1)
			return (perror_file(), TRUE);
	}
	lexer->pipefds[1] = fd;
	return (FALSE);
}

t_bool	set_fd_append_to_file(const char *pathname, t_lexer *lexer)
{
	int	fd;

	if (lexer->pipefds[1] > 2)
		close(lexer->pipefds[1]);
	fd = access(pathname, F_OK);
	if (fd == -1)
	{
		fd = open(pathname, O_CREAT | O_APPEND,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		if (fd == -1)
			return (perror_file(), TRUE);
	}
	else
	{
		fd = access(pathname, W_OK);
		if (fd == -1)
			return (perror_file(), TRUE);
		fd = open(pathname, O_APPEND,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		if (fd == -1)
			return (perror_file(), TRUE);
	}
	lexer->pipefds[1] = fd;
	return (FALSE);
}

t_bool	set_fd_from_file(const char *pathname, t_lexer *lexer)
{
	int	fd;

	if (lexer->pipefds[0] > 2)
		close(lexer->pipefds[0]);
	fd = access(pathname, F_OK);
	if (fd == -1)
		return (perror_file(), TRUE);
	else
	{
		fd = access(pathname, R_OK);
		if (fd == -1)
			return (perror_file(), TRUE);
		fd = open(pathname, O_RDONLY,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		if (fd == -1)
			return (perror_file(), TRUE);
	}
	lexer->pipefds[0] = fd;
	return (FALSE);
}

t_bool	set_fd_heredoc(const char *end, t_lexer *lexer)
{
	char	*line;
	int		fd;
	size_t	len;
	ssize_t	written_bytes;

	if (lexer->pipefds[0] > 2)
		close(lexer->pipefds[0]);
	fd = access(".heredoc", F_OK);
	if (fd == -1)
		fd = open(".heredoc", O_CREAT | O_WRONLY,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	else
		fd = open(".heredoc", O_WRONLY,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if (fd == -1)
		return (perror_file(), TRUE);
	written_bytes = 0;
	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
			return (TRUE);
		len = ft_strlen(line);
		if (ft_strncmp(line, end, len) == 0)
			break ;
		written_bytes = write(fd, line, len);
		if (written_bytes != (ssize_t)len)
			return (free(line), printf("%sError%s\n", RED, WHITE), TRUE);
		written_bytes = write(fd, "\n", 1);
		if (written_bytes != (ssize_t)1)
			return (free(line), printf("%sError%s\n", RED, WHITE), TRUE);
		free(line);
	}
	return (free(line), FALSE);
}
