/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_variables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 00:02:15 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/19 13:06:31 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*get_variable_placeholder(char *line, size_t *i, char **variable_name)
{
	t_bool	brackets;
	size_t	len;

	if (!line)
		return (NULL);
	if (line[*i] && !ft_followed_chars(line + *i, '{', '}'))
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
		return (NULL);
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
		return (free(variable_name), NULL);
	return (free(variable_name), env);
}

char	*substitute_line(char *line, const char *substr,
	const char *replacement, size_t *i)
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
		return (free(line), NULL);
	ft_memcpy(new_line, line, pos - line);
	ft_memcpy(new_line + (pos - line), replacement, lens[2]);
	ft_memcpy(new_line + (pos - line) + lens[2], pos + lens[1],
		line + lens[0] - (pos + lens[1]));
	new_line[lens[0] + (lens[2] - lens[1])] = '\0';
	(*i) += lens[2];
	return (free(line), new_line);
}

t_bool	scan_line(char *line, size_t *i)
{
	while (line[*i] && line[*i + 1])
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
	return (TRUE);
}

char	*substitute_variables(char *line, size_t i)
{
	char	*variable_placeholder;
	char	*variable_name;
	char	*var;

	if (!line || !line[i] || !ft_strchr(line, '$'))
		return (line);
	if (scan_line(line, &i))
		return (line);
	variable_name = NULL;
	variable_placeholder = get_variable_placeholder(line, &i, &variable_name);
	if (!variable_placeholder)
		return (free(line), NULL);
	var = set_env_variable(variable_name);
	if (!var)
	{
		free(variable_placeholder);
		return (free(line), NULL);
	}
	line = substitute_line(line, variable_placeholder, var, &i);
	free(variable_placeholder);
	free(var);
	if (!line)
		return (free(line), NULL);
	return (substitute_variables(line, i));
}
