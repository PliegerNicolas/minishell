/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:48:59 by nicolas           #+#    #+#             */
/*   Updated: 2023/06/22 13:03:39 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static enum e_redir_type	set_redir_type(const char *s, size_t *i)
{
	if (!s)
		return (no_redir);
	if (ft_strncmp(s, "<<", 2) == 0)
		return (*i += 2, heredoc);
	else if (ft_strncmp(s, ">>", 2) == 0)
		return (*i += 2, append_to_file);
	else if (ft_strncmp(s, "<", 1) == 0)
		return (*i += 1, from_file);
	else if (ft_strncmp(s, ">", 1) == 0)
		return (*i += 1, to_file);
	else
		return (perror_parse_error(), error);
}

static char	*get_redir_path(const char *s, size_t *i)
{
	char	*redir_path;
	size_t	j;

	j = 0;
	while (s[*i + j] && is_inset(s[*i + j], "<>"))
		j++;
	while (s[*i + j] && !is_inset(s[*i + j], "<>") && !ft_isspace(s[*i + j]))
		j++;
	redir_path = ft_substr(s, *i, j);
	*i += j;
	if (!redir_path)
		return (perror_malloc("@redir_path (srcs/parsing/set_redirection.c #get\
_redir_path)"), NULL);
	return (redir_path);
}

static t_bool	overwrite_redirection(t_lexer *lexer)
{
	int		fd;

	if (lexer->redir_type[1] != to_file)
		return (FALSE);
	if (!lexer->redir_path[1])
		return (TRUE);
	if (access(lexer->redir_path[1], F_OK) == 0
		&& access(lexer->redir_path[1], W_OK) == -1)
	{
		if (!lexer->err)
			perror("access");
		lexer->err = TRUE;
	}
	else
	{
		fd = open_file(lexer, lexer->redir_path[1], lexer->redir_type[1]);
		if (fd == -1)
			return (perror("open"), TRUE);
		close(fd);
	}
	return (FALSE);
}

static t_bool	set_redir_lexer_variables(t_lexer *lexer, char *redir_path,
	enum e_redir_type *redir_type, char ***envp)
{
	t_bool	slot;

	slot = 0;
	if (*redir_type == to_file || *redir_type == append_to_file)
	{
		slot = 1;
		if (lexer->redir_type[slot] && overwrite_redirection(lexer))
			return (TRUE);
	}
	if (lexer->err == TRUE)
		return (TRUE);
	if (lexer->redir_path[slot])
		free(lexer->redir_path[slot]);
	lexer->redir_type[slot] = *redir_type;
	*redir_type = no_redir;
	if (lexer->redir_type[slot] == heredoc)
	{
		if (set_redir_path_heredoc(redir_path, lexer, envp))
			return (free(redir_path), TRUE);
		free(redir_path);
	}
	else
		lexer->redir_path[slot] = redir_path;
	return (FALSE);
}

t_bool	set_redirection(const char *s, t_lexer *lexer,
	enum e_redir_type *redir_type, char ***envp)
{
	char	*redir_path;
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (*redir_type == no_redir)
			*redir_type = set_redir_type(s + i, &i);
		if (*redir_type == error)
			return (TRUE);
		if (!s[i])
			return (FALSE);
		redir_path = get_redir_path(s, &i);
		if (!redir_path)
			return (TRUE);
		if (set_redir_lexer_variables(lexer, redir_path, redir_type, envp))
			return (TRUE);
	}
	return (FALSE);
}
