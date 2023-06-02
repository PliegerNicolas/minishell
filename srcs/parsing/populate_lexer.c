/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_lexer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:34:17 by nicolas           #+#    #+#             */
/*   Updated: 2023/06/02 11:03:55 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

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

static t_bool	str_is_redirection(const char *str)
{
	if (!str)
		return (FALSE);
	if (*str && (*str == '<' || *str == '>'))
		return (TRUE);
	return (FALSE);
}

static t_bool	group_lexer_args(t_lexer *lexer)
{
	char	**new_lexer;
	char	*exec;

	if (!lexer)
		return (FALSE);
	if (lexer->options || lexer->args)
	{
		new_lexer = ft_join_str_arr(lexer->options, lexer->args);
		if (!new_lexer)
			return (TRUE);
	}
	exec = ft_strdup(lexer->exec);
	if (!exec)
		return (free_str_arr(new_lexer), TRUE);
	new_lexer = ft_prepend_to_string_array(new_lexer, exec);
	if (!new_lexer)
		return (TRUE);
	free_str_arr(lexer->args);
	lexer->args = new_lexer;
	return (FALSE);
}

static t_bool	fill_lexer(t_lexer *lexer, char **split, char ***envp)
{
	size_t	i;
	t_bool	prev_is_redir;

	i = 0;
	prev_is_redir = FALSE;
	while (split[i])
	{
		if (lexer->exec && str_is_option(split[i]))
		{
			if (set_options(split[i], lexer))
				return (TRUE);
		}
		else if (prev_is_redir || str_is_redirection(split[i]))
		{
			if (set_redirection(split[i], lexer, &prev_is_redir, envp))
				return (TRUE);
		}
		else if (set_arguments(split[i], lexer, envp))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

t_lexer	*populate_lexer(t_lexer *lexer, enum e_quote_status q_status,
	char ***envp)
{
	char	**split;

	if (!lexer)
		return (NULL);
	split = ft_setsplit_quotesafe(lexer->cmd, WHITE_SPACES, q_status);
	if (!split)
		return (free_lexer(lexer), NULL);
	if (fill_lexer(lexer, split, envp))
		return (free_lexer(lexer), free_str_arr(split), NULL);
	free_str_arr(split);
	if (group_lexer_args(lexer))
		return (free_lexer(lexer), NULL);
	return (lexer);
}
