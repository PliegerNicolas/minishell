/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_variables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 00:02:15 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/20 14:43:46 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/*
	This function retrieves the variable's placeholder value and it's
	name via pointer.

	A variable placeholder can take two forms :
	- $VARIABLE_NAME
	- ${VARIABLE_NAME}

	In case of unclosed brackets, it returns an error message.
*/
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
		return (perror_malloc("@variable_name \
(srcs/parsing/substitute_variables.c #substitute_variables)"), NULL);
	return (ft_substr(line, *i, len - !brackets));
}

/*
	This function returns the value of a given variable.
	It find's most of it's values in the environnement.
	
	Returns a a string or an empty string if no variable value found.
	The string is always malloced.
*/
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
		perror_malloc("@env (srcs/parsing/substitute_variables.c \
#set_env_variable)");
		return (free(variable_name), NULL);
	}
	return (free(variable_name), env);
}

/*
	This function substitutes the first found substr by a replacement string.
	In our case the variable_placeholder by it's value.

	@line : original line.
	@substr : the variable_placeholder.
	@replacemement : the variable's value.
	@pos : the position of the substring in the original line.
	@lens[] : [0] = line length, [1] = substr length, [2] = replacement length.

	Returns the new line with substituted value.
*/
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
	{
		perror_malloc("@new_line (srcs/parsing/substitute_variables.c \
#substitute_line)");
		return (free(line), NULL);
	}
	ft_memcpy(new_line, line, pos - line);
	ft_memcpy(new_line + (pos - line), replacement, lens[2]);
	ft_memcpy(new_line + (pos - line) + lens[2], pos + lens[1],
		line + lens[0] - (pos + lens[1]));
	new_line[lens[0] + (lens[2] - lens[1])] = '\0';
	(*i) += lens[2];
	return (free(line), new_line);
}

/*
	This function runs through the line to find a valid command indicator.
	It updates i accordingly.

	- ft_isspace() : verifies if character is a space character.

	Returns TRUE or FALSE.
	TRUE if there is no valid command found.
	FALSE if there is a valid command found.
*/
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

/*
	This function substitutes variables by their value recursivly.

	@variable_placeholder : It contains the variable's
							placeholder (ex : $USER or ${USER}).
	@variable_name : contains the variable's name (ex : "USER").
	@var : contains the variable's value (ex : "nicolas").

	- get_variable_placeholder() : this function returns the placeholder
								   and the variable's name via pointer.
	- set_env_variable() : this function returns the variable's value
						   if found or an empty string.

	Returns a line with substituted variables.
*/
char	*substitute_variables(char *line, size_t i)
{
	char	*variable_placeholder;
	char	*variable_name;
	char	*var;

	if (!line || !line[i] || !ft_strchr(line, '$') || scan_line(line, &i))
		return (line);
	variable_name = NULL;
	variable_placeholder = get_variable_placeholder(line, &i, &variable_name);
	if (!variable_placeholder)
		return (free(line), NULL);
	var = set_env_variable(variable_name);
	if (!var)
		return (free(variable_placeholder), free(line), NULL);
	line = substitute_line(line, variable_placeholder, var, &i);
	free(variable_placeholder);
	free(var);
	if (!line)
	{
		perror_malloc("@line (srcs/parsing/substitute_variables.c \
#substitute_variables)");
		return (free(line), NULL);
	}
	return (substitute_variables(line, i));
}
