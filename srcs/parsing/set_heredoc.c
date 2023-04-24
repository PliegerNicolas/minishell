/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 13:06:31 by nicolas           #+#    #+#             */
/*   Updated: 2023/04/24 14:19:49 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static char	*set_heredoc_filename(t_lexer *lexer)
{
	char	*heredoc;
	char	*id;

	if (!lexer)
		return (NULL);
	id = ft_itoa(lexer->id);
	if (!id)
		return (perror_malloc("@id (srcs/parsing/set_heredoc.c \
#heredoc_filename)"), NULL);
	heredoc = ft_strjoin(".heredoc_", id);
	free(id);
	if (!heredoc)
		return (perror_malloc("@heredoc (srcs/parsing/set_heredoc.c \
#heredoc_filename)"), NULL);
	return (heredoc);
}

static char	*heredoc_prompt(t_lexer *lexer)
{
	char	*id;
	char	*temp_prompt;
	char	*prompt;

	if (!lexer)
		return (NULL);
	id = ft_itoa(lexer->id);
	if (!id)
		return (perror_malloc("@id (srcs/parsing/set_heredoc.c \
#heredoc_prompt)"), NULL);
	temp_prompt = ft_strjoin("heredoc ", id);
	free(id);
	if (!temp_prompt)
		return (perror_malloc("@temp_prompt (srcs/parsing/set_heredoc.c \
#heredoc_prompt)"), NULL);
	prompt = ft_strjoin(temp_prompt, " > ");
	free(temp_prompt);
	if (!prompt)
		return (perror_malloc("@prompt (srcs/parsing/set_heredoc.c \
#heredoc_prompt)"), NULL);
	return (prompt);
}

static t_bool	fill_heredoc(char *line, const int fd, const size_t len)
{
	ssize_t	written_bytes;

	if (!line)
		return (TRUE);
	written_bytes = write(fd, line, len);
	if (written_bytes != (ssize_t)len)
		return (perror_heredoc(), TRUE);
	written_bytes = write(fd, "\n", 1);
	if (written_bytes != (ssize_t)1)
		return (perror_heredoc(), TRUE);
	return (FALSE);
}

static t_bool	write_to_heredoc(t_lexer *lexer, const int fd, const char *end)
{
	char	*prompt;
	char	*line;
	size_t	len;

	while (1)
	{
		prompt = heredoc_prompt(lexer);
		if (!prompt)
			return (TRUE);
		line = readline(prompt);
		free(prompt);
		if (!line)
			return (TRUE);
		line = substitute_line_content(line, 0, none);
		if (!line)
			return (TRUE);
		len = ft_strlen(line);
		if (ft_strncmp(line, end, len) == 0)
			return (free(line), FALSE);
		if (fill_heredoc(line, fd, len))
			return (free(line), TRUE);
		free(line);
	}
	return (FALSE);
}

t_bool	set_redir_path_heredoc(const char *end, t_lexer *lexer)
{
	int		fd;
	char	*heredoc;

	if (!end)
		return (FALSE);
	if (lexer->redir_path[0])
		free(lexer->redir_path[0]);
	heredoc = set_heredoc_filename(lexer);
	if (!heredoc)
		return (TRUE);
	fd = open(heredoc, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (perror_file(), TRUE);
	if (write_to_heredoc(lexer, fd, end))
		return (TRUE);
	if (close(fd) == -1)
		return (perror_file(), TRUE);
	lexer->redir_path[0] = heredoc;
	if (!lexer->redir_path[0])
		return (perror_malloc("lexer->lexer_redir (srcs/parsing/set_redirection\
_2.c #set_redir_path_heredoc)"), TRUE);
	return (FALSE);
}
