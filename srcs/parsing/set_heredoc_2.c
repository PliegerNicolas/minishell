/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_heredoc_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 19:20:25 by nicolas           #+#    #+#             */
/*   Updated: 2023/06/04 20:14:06 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

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

t_bool	write_to_heredoc(t_lexer *lexer, const int fd,
	const char *end, char ***envp)
{
	char	*prompt;
	char	*line;
	size_t	len;

	while (1)
	{
		prompt = heredoc_prompt(lexer);
		if (!prompt)
			return (g_status = general_failure, TRUE);
		line = readline(prompt);
		free(prompt);
		if (!line && g_status == termination_by_ctrl_c)
			return (TRUE);
		else if (!line)
			return (perror_heredoc_eof((char *)end), FALSE);
		line = substitute_line_content(line, 0, none, envp);
		if (!line)
			return (g_status = general_failure, TRUE);
		len = ft_strlen(line);
		if (ft_strncmp(line, end, len + 1) == 0)
			return (free(line), FALSE);
		if (fill_heredoc(line, fd, len))
			return (g_status = general_failure, free(line), TRUE);
		free(line);
	}
}
