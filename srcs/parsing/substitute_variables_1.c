/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_variables_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 00:02:15 by nicolas           #+#    #+#             */
/*   Updated: 2023/05/20 17:01:01 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static t_bool	is_between_quotes(char c, enum e_quote_status *quote_status)
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
		if (is_between_quotes(line[*i], quote_status) && *quote_status == single_quote)
			(*i)++;
		else if (line[*i + 1])
		{
			if (line[*i] == '\\')
				(*i) += 2;
			else if (line[*i] == '$' && line[*i + 1] == '$')
				(*i)++;
			else if (line[*i] == '$' && (line[*i + 1] == '\'' || line[*i + 1] == '\"'))
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

static size_t	variable_placeholder_len(char *line, size_t i)
{
	size_t	j;

	j =  1;
	if (line[i + j] == '{')
	{
		if (!ft_strchr(line + i + j, '}'))
			return (0);
		while (line[i + j] != '}' && line[i + j] != '\\')
		{
			if (line[i + j] == '\'' || line[i + j] == '\"')
				return (0);
			j++;
		}
		j++;
	}
	else
	{
		while (line[i + j] && !ft_isspace(line[i + j]) && line[i + j] != '\\')
		{
			if (line[i + j] == '}')
				return (0);
			else if (line[i + j] == '$' || line[i + j] == '\'' || line[i + j] == '\"')
				break ;
			j++;
		}
	}
	return (j);
}

static char	*find_variable_value(char *line, size_t j, char ***envp)
{
	char	*variable_name;
	char	*variable_value;

	if (!line)
		return (NULL);
	if (line[1] == '{')
		variable_name = ft_substr(line, 2, j - 3);
	else
		variable_name = ft_substr(line, 1, j - 1);
	if (!variable_name)
		return (perror_malloc("test2"), NULL);
	variable_value = get_env_var(variable_name, (const char **)*envp);
	free(variable_name);
	if (!variable_value)
		variable_value = ft_strdup("");
	if (!variable_value)
		return (perror_malloc("test3"), NULL);
	return (variable_value);
}

static t_bool	substitute_variable(char **line, size_t i, char ***envp)
{
	char	*variable_placeholder;
	char	*variable_value;
	size_t	j;

	if (!*line)
		return (TRUE);
	j = variable_placeholder_len(*line, i);
	if (j == 0)
		return (perror_bad_substitution(), free(*line), TRUE);
	variable_placeholder = ft_substr(*line + i, 0, j);
	if (!variable_placeholder)
		return (perror_malloc("test1"), free(*line), TRUE);
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
		return (line);
	if (substitute_variable(&line, i, envp))
		return (NULL);
	return (substitute_line_content(line, i, quote_status, envp));
}
/*
static t_bool	scan_line(char *line, size_t *i,
	enum e_quote_status *quote_status)
{
	while (line[*i] && line[*i + 1])
	{
		if (set_quotestatus(line + *i, quote_status))
			(*i)++;
		else if (*quote_status == single_quote)
			(*i)++;
		else
		{
			if (line[*i] == '$' && line[*i + 1] == '$')
				(*i)++;
			else if (line[*i] == '$' && (line[*i + 1] == '\''
					|| line[*i + 1] == '\"'))
				(*i)++;
			else if (line[*i] == '$' && !ft_isspace(line[*i + 1]))
				return (FALSE);
			else
				(*i)++;
		}
	}
	return (TRUE);
}

static char	**get_var_landmarks(char *line, size_t i, char ***envp)
{
	char	**var_landmarks;
	t_bool	brackets;

	if (!line && !*line)
		return (NULL);
	if (line[i] && !ft_followed_chars(line + i, '{', '}'))
		return (perror_bad_substitution(), NULL);
	brackets = FALSE;
	if (line[i + 1] && line[i + 1] == '{')
		brackets = TRUE;
	var_landmarks = set_var_landmarks(line, i, brackets, envp);
	if (!var_landmarks)
		return (NULL);
	return (var_landmarks);
}

char	*substitute_line_content(char *line, size_t i,
	enum e_quote_status quote_status, char ***envp)
{
	char	**var_landmarks;

	if (!line || !line[i] || scan_line(line, &i, &quote_status))
		return (line);
	var_landmarks = get_var_landmarks(line, i, envp);
	if (!var_landmarks)
		return (free(line), NULL);
	line = replace_first(line, var_landmarks[0], var_landmarks[2]);
	free_str_arr(var_landmarks);
	return (substitute_line_content(line, i, quote_status, envp));
}
*/
