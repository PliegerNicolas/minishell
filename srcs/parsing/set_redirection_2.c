/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirection_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 01:49:13 by nicolas           #+#    #+#             */
/*   Updated: 2023/04/24 13:07:22 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_bool	set_redir_path(char *pathname, t_lexer *lexer, int slot)
{
	if (!pathname)
		return (TRUE);
	if (lexer->redir_path[slot])
		free(lexer->redir_path[slot]);
	lexer->redir_path[slot] = pathname;
	return (FALSE);
}

/*
static t_bool	write_to_heredoc(const int fd, const char *end)
{
	char	*line;
	ssize_t	written_bytes;
	size_t	len;

	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
			return (TRUE);
		line = substitute_line_content(line, 0, none);
		if (!line)
			return (TRUE);
		len = ft_strlen(line);
		if (ft_strncmp(line, end, len) == 0)
			return (free(line), FALSE);
		written_bytes = write(fd, line, len);
		if (written_bytes != (ssize_t)len)
			return (free(line), printf("%sError%s\n", RED, WHITE), TRUE);
		written_bytes = write(fd, "\n", 1);
		if (written_bytes != (ssize_t)1)
			return (free(line), printf("%sError%s\n", RED, WHITE), TRUE);
		free(line);
	}
	return (FALSE);
}

t_bool	set_redir_path_heredoc(const char *end, t_lexer *lexer)
{
	int		fd;

	if (!end)
		return (FALSE);
	if (lexer->redir_path[0])
		free(lexer->redir_path[0]);
	fd = access(".heredoc", F_OK);
	if (fd == -1)
		fd = open(".heredoc", O_CREAT | O_WRONLY, 0644);
	else
		fd = open(".heredoc", O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (perror_file(), TRUE);
	if (write_to_heredoc(fd, end))
		return (TRUE);
	if (close(fd) == -1)
		return (perror_file(), TRUE);
	lexer->redir_path[0] = ft_strdup(".heredoc");
	if (!lexer->redir_path[0])
		return (perror_malloc("lexer->lexer_redir (srcs/parsing/set_redirection\
_2.c #set_redir_path_heredoc)"), TRUE);
	return (FALSE);
}
*/
