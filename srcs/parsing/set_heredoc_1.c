/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_heredoc_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 13:06:31 by nicolas           #+#    #+#             */
/*   Updated: 2023/05/16 19:40:54 by nicolas          ###   ########.fr       */
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

t_bool	set_and_fill_heredoc(t_lexer *lexer, const char *end, char ***envp)
{
	int	fd;
	int	stdin_cpy;

	fd = open(lexer->redir_path[0], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (perror_file(), g_status = general_failure, TRUE);
	stdin_cpy = dup(STDIN_FILENO);
	signal(SIGINT, sigint_heredoc_handler);
	
	if (write_to_heredoc(lexer, fd, end, envp))
	{
		dup2(stdin_cpy, STDIN_FILENO);
		return (close(stdin_cpy), close(fd), TRUE);
	}

	setup_signals(sigint_handler);
	return (close(stdin_cpy), close(fd), g_status = general_failure, FALSE);
}

t_bool	set_redir_path_heredoc(const char *end, t_lexer *lexer, char ***envp)
{
	if (!end)
		return (g_status = general_failure, FALSE);
	if (lexer->redir_path[0])
		free(lexer->redir_path[0]);
	lexer->redir_path[0] = set_heredoc_filename(lexer);
	if (!lexer->redir_path[0])
		return (g_status = general_failure, TRUE);
	if (set_and_fill_heredoc(lexer, end, envp))
		return (TRUE);
	if (!lexer->redir_path[0])
		return (perror_malloc("lexer->lexer_redir (srcs/parsing/set_redirection\
_2.c #set_redir_path_heredoc)"), g_status = general_failure, TRUE);
	return (FALSE);
}
