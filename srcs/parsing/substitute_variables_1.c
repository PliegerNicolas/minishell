/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_variables_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 00:02:15 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/22 17:40:24 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/*
static t_bool	advance_through_line(char *line, size_t *i,
	enum e_quote_status *quote_status)
{
	while (line[*i] && line[*i + 1])
	{
		if (set_quotestatus(line[*i], quote_status))
			(*i)++;
		else if (*quote_status == single_quote)
			(*i)++;
		else
		{
			if (line[*i] != '$' || (line[*i] == '$' && ft_isspace(line[*i + 1])))
				(*i)++;
			else if (line[*i + 1] && line[*i + 1] == '$')
				(*i)++;
			else if (line[*i + 1] && ft_isspace(line[*i]))
				(*i)++;
			else
				return (FALSE);
		}
	}
	return (TRUE);
}

char	*get_variable_placeholder(char *line, size_t *i, char **variable_name,
	enum e_quote_status *quote_status)
{
	t_bool	brackets;
	size_t	len;

	if (!line)
		return (NULL);
	if (line[*i] && !ft_followed_chars_quotesafe(line + *i, '{', '}', *quote_status))
		return (perror_bad_substitution(), NULL);
	brackets = FALSE;
	len = 1;
	if (line[*i + len] == '{')
		brackets = TRUE;
	if (brackets)
		while (line[*i + len] && line[*i + len] != '}')
			len++;
	else
		while (line[*i + len] && !ft_isspace(line[*i + len])
			&& line[*i + len] != '$')
			len++;
	len++;
	*variable_name = ft_substr(line, *i + brackets + 1, len - brackets - 2);
	if (!*variable_name)
		return (perror_malloc("@variable_name \
(srcs/parsing/substitute_variables.c #substitute_variables)"), NULL);
	return (ft_substr(line, *i, len - !brackets));
}

char	*set_env_variable(char *variable_name)
{
	char	*env;
	char	*temp_env;

	if (!variable_name)
		return (NULL);
	if (ft_strncmp(variable_name, "?", 2) == 0)
		env = ft_itoa(g_status);
	else
	{
		temp_env = getenv(variable_name);
		if (!temp_env)
			temp_env = "";
		env = ft_strdup(temp_env);
	}
	if (!env)
	{
		perror_malloc("@env \
(srcs/parsing/substitute_variables.c #set_env_variable)");
		return (free(variable_name), NULL);
	}
	return (free(variable_name), env);
}

static char	*substitute_variable(char *line, const char *substr,
	const char *replacement)
{
	char	*new_line;
	char	*pos;
	size_t	lens[3];

	if (!line || !substr || !replacement)
		return (line);
	lens[0] = ft_strlen(line);
	pos = ft_strnstr(line, substr, lens[0]);
	lens[1] = ft_strlen(substr);
	lens[2] = ft_strlen(replacement);
	new_line = malloc((lens[0] + lens[2] - lens[1] + 1) * sizeof(*new_line));
	if (!new_line)
	{
		perror_malloc("@variable_name \
(srcs/parsing/substitute_variables.c #substitute_variables)");
		return (free(line), NULL);
	}
	ft_memcpy(new_line, line, pos - line);
	ft_memcpy(new_line + (pos - line), replacement, lens[2]);
	ft_memcpy(new_line + (pos - line) + lens[2], pos + lens[1],
		line + lens[0] - (pos + lens[1]));
	new_line[lens[0] + (lens[2] - lens[1])] = '\0';
	return (free(line), new_line);
}

char	*substitute_line_content(char *line, size_t i,
	enum e_quote_status quote_status)
{
	char	*variable_placeholder;
	char	*variable_name;
	char	*var;

	if (!line || !line[i] || advance_through_line(line, &i, &quote_status))
		return (line);
	variable_name = NULL;
	variable_placeholder = get_variable_placeholder(line, &i, &variable_name, &quote_status);
	if (!variable_placeholder)
		return (free(line), NULL);
	var = set_env_variable(variable_name);
	if (!var)
		return (free(variable_placeholder), free(line), NULL);
	line = substitute_variable(line, variable_placeholder, var);
	free(variable_placeholder);
	free(var);
	return (substitute_line_content(line, i, quote_status));
}
*/

static t_bool	scan_line(char *line, size_t *i, enum e_quote_status *quote_status)
{
	while (line[*i] && line[*i + 1])
	{
		if (set_quotestatus(line[*i], quote_status))
			(*i)++;
		else if (*quote_status == single_quote)
			(*i)++;
		else
		{
			if (line[*i] == '$' && line[*i + 1] == '$')
				(*i)++;
			else if (line[*i] == '$' && (line[*i + 1] == '\'' || line[*i + 1] == '\"'))
				(*i)++;
			else if (line[*i] == '$' && !ft_isspace(line[*i + 1]))
				return (FALSE);
			else
				(*i)++;
		}
	}
	return (TRUE);
}

char	**get_variable_landmarks(char *line, size_t i)
{
	char	**variable_landmarks;
	size_t	len;
	t_bool	brackets;

	if (!line && !*line)
		return (NULL);
	if (line[i] && !ft_followed_chars(line + i, '{', '}'))
		return (perror_bad_substitution(), NULL);
	len = 0;
	brackets = FALSE;
	if (line[i + 1] && line[i + 1] == '{')
		brackets = TRUE;
	if (brackets)
		while (line[i + len] && line[i + len] != '}')
			len++;
	else
	{
		while (line[i + len])
		{
			if (len && line[i + len] == '$')
				break ;
			else if (ft_isspace(line[i + len]))
				break ;
			else if (line[i + len] == '\'' || line[i + len] == '\"')
				break ;
			len++;
		}
	}
	variable_landmarks = set_variable_landmarks(line, i, ++len, brackets);
	if (!variable_landmarks)
		return (NULL);
	return (variable_landmarks);
}

static char	*substitute_variable(char *line, const char *substr,
	const char *replacement)
{
	char	*new_line;
	char	*pos;
	size_t	lens[3];

	if (!line || !substr || !replacement)
		return (line);
	lens[0] = ft_strlen(line);
	pos = ft_strnstr(line, substr, lens[0]);
	lens[1] = ft_strlen(substr);
	lens[2] = ft_strlen(replacement);
	new_line = malloc((lens[0] + lens[2] - lens[1] + 1) * sizeof(*new_line));
	if (!new_line)
	{
		perror_malloc("@variable_name (srcs/parsing/substitute_variables.c #substitute_variables)");
		return (free(line), NULL);
	}
	ft_memcpy(new_line, line, pos - line);
	ft_memcpy(new_line + (pos - line), replacement, lens[2]);
	ft_memcpy(new_line + (pos - line) + lens[2], pos + lens[1],
		line + lens[0] - (pos + lens[1]));
	new_line[lens[0] + (lens[2] - lens[1])] = '\0';
	return (free(line), new_line);
}

char	*substitute_line_content(char *line, size_t i, enum e_quote_status quote_status)
{
	char	**variable_landmarks;

	if (!line || !line[i] || scan_line(line, &i, &quote_status))
		return (line);
	variable_landmarks = get_variable_landmarks(line, i);
	if (!variable_landmarks)
		return (free(line), NULL);
	line = substitute_variable(line, variable_landmarks[0], variable_landmarks[2]);
	free_str_arr(variable_landmarks); // temp
	return (substitute_line_content(line, ++i, quote_status));
}
