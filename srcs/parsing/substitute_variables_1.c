/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_variables_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 00:02:15 by nicolas           #+#    #+#             */
/*   Updated: 2023/05/21 01:45:27 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_bool	is_between_quotes(char c, enum e_quote_status *quote_status)
{
	if (!c)
		return (FALSE);
	if (*quote_status == none && c == '\'')
		*quote_status = single_quote;
	else if (*quote_status == none && c == '\"')
		*quote_status = double_quote;
	else if (*quote_status == single_quote && c == '\'')
		*quote_status = none;
	else if (*quote_status == double_quote && c == '\"')
		*quote_status = none;
	else if (*quote_status == none)
		return (FALSE);
	return (TRUE);
}

static t_bool	scan_through_line(char *line, size_t *i,
	enum e_quote_status *quote_status)
{
	if (!line)
		return (TRUE);
	while (line[*i])
	{
		if (is_between_quotes(line[*i], quote_status)
			&& *quote_status == single_quote)
			(*i)++;
		else if (line[*i + 1])
		{
			if (line[*i] == '\\')
				(*i) += 2;
			else if (line[*i] == '$' && is_inset(line[*i + 1], "$\\"))
				(*i)++;
			else if (line[*i] == '$' && !ft_isspace(line[*i + 1]))
				return (FALSE);
			else
				(*i)++;
		}
		else
			(*i)++;
	}
	return (TRUE);
}

static size_t	variable_placeholder_len(char *s)
{
	size_t	i;

	i = 1;
	if (s[i] == '{')
	{
		if (!ft_strchr(s + i, '}'))
			return (0);
		while (!is_inset(s[i], "}\\"))
			if (is_inset(s[i++], "\'\""))
				return (0);
		i++;
	}
	else
	{
		while (s[i] && !ft_isspace(s[i]) && s[i] != '\\')
		{
			if (s[i] == '}')
				return (0);
			else if (is_inset(s[i], "$\'\"=") || (s[i - 1] && s[i - 1] == '?'))
				break ;
			i++;
		}
	}
	return (i);
}

static t_bool	substitute_variable(char **line, size_t i, char ***envp)
{
	char	*variable_placeholder;
	char	*variable_value;
	size_t	j;

	if (!*line)
		return (TRUE);
	j = variable_placeholder_len((*line) + i);
	if (j == 0)
		return (perror_bad_substitution(), free(*line), TRUE);
	variable_placeholder = ft_substr(*line + i, 0, j);
	if (!variable_placeholder)
		return (perror_malloc("@variable_placeholder (srcs/parsing/substitute_v\
ariables_1.c #substitute_variable)"), free(*line), TRUE);
	variable_value = find_variable_value(*line + i, j, envp);
	if (!variable_value)
		return (free(variable_placeholder), free(*line), TRUE);
	*line = replace_first(*line, variable_placeholder, variable_value);
	free(variable_placeholder);
	free(variable_value);
	if (!*line)
		return (TRUE);
	return (FALSE);
}

char	*substitute_line_content(char *line, size_t i,
	enum e_quote_status quote_status, char ***envp)
{
	if (!line)
		return (NULL);
	if (scan_through_line(line, &i, &quote_status))
	{
		line = replace_escaped_characters(line, 0, none);
		if (!line)
			return (NULL);
		return (line);
	}
	if (substitute_variable(&line, i, envp))
		return (NULL);
	return (substitute_line_content(line, i, quote_status, envp));
}
