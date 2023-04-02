/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirection_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:48:59 by nicolas           #+#    #+#             */
/*   Updated: 2023/04/02 04:02:37 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static char	*get_quoteless_str(const char *str, t_bool *prev_is_redir)
{
	char	*quoteless_str;

	if (!str)
		return (NULL);
	quoteless_str = ft_strdup(str);
	if (!quoteless_str)
		return (perror_malloc("@quoteless_str (srcs/parsing/set_options.c #get_\
quoteless_str)"), NULL);
	quoteless_str = remove_quotes(quoteless_str, none);
	if (!quoteless_str)
		return (NULL);
	*prev_is_redir = FALSE;
	return (quoteless_str);
}

static t_bool	set_redir_type(const char *str, size_t *i, t_lexer *lexer)
{
	enum e_redir_type	redir_type;

	if (!str)
		return (no_redir);
	redir_type = no_redir;
	while (str[*i] && (str[*i] == '<' || str[*i] == '>'))
	{
		if (str[*i] == '<' && redir_type == no_redir)
			redir_type = from_file;
		else if (str[*i] == '<' && redir_type == from_file)
			redir_type = heredoc;
		else if (str[*i] == '>' && redir_type == no_redir)
			redir_type = to_file;
		else if (str[*i] == '>' && redir_type == to_file)
			redir_type = append_to_file;
		else
			return (perror_parse_error(), no_redir);
		(*i)++;
	}
	if (redir_type == 1 || redir_type == 2)
		lexer->redir_type[1] = redir_type;
	else
		lexer->redir_type[0] = redir_type;
	return (redir_type);
}

static t_bool	set_fds(char *pathname, t_lexer *lexer,
	enum e_redir_type redir_type)
{
	if (!pathname)
		return (FALSE);
	if (redir_type == to_file)
	{
		if (set_fd_to_file(pathname, lexer))
			return (TRUE);
	}
	else if (redir_type == append_to_file)
	{
		if (set_fd_append_to_file(pathname, lexer))
			return (TRUE);
	}
	else if (redir_type == from_file)
	{
		if (set_fd_from_file(pathname, lexer))
			return (TRUE);
	}
	else if (redir_type == heredoc)
	{
		if (set_fd_heredoc(pathname, lexer))
			return (TRUE);
	}
	return (FALSE);
}

t_bool	set_redirection(const char *str, t_lexer *lexer, t_bool *prev_is_redir)
{
	char						*quoteless_str;
	static enum e_redir_type	redir_type;
	size_t						i;

	if (!str)
		return (FALSE);
	if (!redir_type)
		redir_type = no_redir;
	i = 0;
	if (*prev_is_redir)
		quoteless_str = get_quoteless_str(str, prev_is_redir);
	else
	{
		redir_type = set_redir_type(str, &i, lexer);
		if (!str[i])
			return (*prev_is_redir = TRUE, FALSE);
		quoteless_str = ft_strdup(str + i);
	}	
	if (!quoteless_str)
		return (TRUE);
	if (set_fds(quoteless_str, lexer, redir_type))
		return (free(quoteless_str), TRUE);
	redir_type = no_redir;
	return (free(quoteless_str), FALSE);
}
