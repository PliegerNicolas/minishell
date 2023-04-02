/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_lexer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:34:17 by nicolas           #+#    #+#             */
/*   Updated: 2023/04/02 02:43:21 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/*
	This function verifies if the given str should be considered as an
	option. It skips potential quotes and verifies the first found character
	that isn't a minishell argument.
	Returns TRUE if it is the case. Else FALSE.
*/
static t_bool	str_is_option(const char *str)
{
	if (!str)
		return (FALSE);
	while (*str && (*str == '\"' || *str == '\''))
		str++;
	if (*str && *str == '-')
		return (TRUE);
	return (FALSE);
}

/*
	This function verifies if the given str should be considered as redirection.
	It skips potential quotes and verifies the first found character that isn't
	a minishell argument.
	Returns TRUE if it is the case. Else FALSE.
*/
static t_bool	str_is_redirection(const char *str)
{
	if (!str)
		return (FALSE);
	if (*str && (*str == '<' || *str == '>'))
		return (TRUE);
	return (FALSE);
}

/*
	This function goes through the splitted string (splitted by '|') and
	calls the expected function :
	- set_exec() : the string containing the executable's name or
				   builtin's name.
	- set_options() : add's the found options characters to the lexer's
					  option argument.
	- set_redirection() : if redirection not already found, fill's thhe
						  lexer's redirection arguments.
	- set_arguments() : If there is data that hasn't been recognized, it
						goes here.
	Return TRUE on error. Else returns  FALSE.
*/
static t_bool	fill_lexer(char **split, t_lexer *lexer)
{
	int		i;
	t_bool	prev_is_redir;

	if (!split)
		return (FALSE);
	prev_is_redir = FALSE;
	i = 0;
	if (split[i] && set_exec(split[i], lexer, &prev_is_redir))
		return (TRUE);
	while (split[++i])
	{
		if (str_is_option(split[i]))
		{
			if (set_options(split[i], lexer))
				return (TRUE);
		}
		else if (prev_is_redir || str_is_redirection(split[i]))
		{
			if (set_redirection(split[i], lexer, &prev_is_redir))
				return (TRUE);
		}
		else if (set_arguments(split[i], lexer))
			return (TRUE);
	}
	return (FALSE);
}

t_lexer	*populate_lexer(t_lexer *lexer, const char *cmd,
	enum e_quote_status quote_status)
{
	char	**split;

	if (!lexer)
		return (NULL);
	split = ft_setsplit_quotesafe(cmd, WHITE_SPACES, quote_status);
	if (!split)
		return (free_lexer(lexer), NULL);
	lexer->cmd = ft_strdup(cmd);
	if (!lexer->cmd)
		return (free_lexer(lexer), NULL);
	lexer->redir_type[0] = no_redir;
	lexer->redir_type[1] = no_redir;
	lexer->pipefds[0] = STDIN;
	lexer->pipefds[1] = STDOUT;
	if (fill_lexer(split, lexer))
		return (free_str_arr(split), free_lexer(lexer), NULL);
	return (free_str_arr(split), lexer);
}
