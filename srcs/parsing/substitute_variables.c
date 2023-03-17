/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_variables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 00:02:15 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/17 19:29:46 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/*
	This function is called by get_next_variable_substr() if
	a '{' as been detected just after a $.
	It then returns the length of the variable.
	Example : "${USER}"; len = 7.
*/
int	variable_len_in_braquet(char *line, size_t *i, int len)
{
	int	braquets;

	braquets = 0;
	if (line[*i + len] == '{')
	{
		len++;
		braquets++;
	}
	while (line[*i + len] && braquets)
	{
		if (line[*i + len] == '{')
			return (perror_bad_substitution(), -1);
		else if (line[*i + len] == '}')
			braquets--;
		len++;
	}
	return (len);
}

/*
	This function returns the substr designating the
	next variable (example : "$USER" or "${USER}").
	If the line is badly constructed (unclosed '{' or extra '}'),
	it returns an NULL and an error message.
	It also moves the cursor (i) around so multiple variables can be read
	through a while loop.
*/
static char	*get_next_variable_substr(char *line, size_t *i)
{
	int	len;

	if (!line || !line[*i])
		return (NULL);
	if (!line[*i])
		return (ft_strdup(""));
	while ((line[*i] && line[*i] != '$') || (line[*i] == '$' && ft_isspace(line[*i + 1])))
		(*i)++;
	if (line[*i] && !ft_followed_chars(line + *i, '{', '}'))
		return (perror_bad_substitution(), NULL);
	len = 0;
	if (line[*i] == '$' && line[*i + 1] && line[*i + 1] == '{')
		len = variable_len_in_braquet(line, i, ++len);
	else if (line[*i] == '$')
	{
		len++;
		while (line[*i + len] && line[*i + len] != '$' && !ft_isspace(line[*i + len])
			&& line[*i + len] != '{' && line[*i + len] != '}')
			len++;
		if (line[*i + len] == '{' || line[*i + len] == '}')
			return (perror_bad_substitution(), NULL);
	}
	if (len < 0)
		return (NULL);
	return (ft_substr(line, *i, len));
}

/*
	This function returns the name of the given variable.
	It should receive as parameter something looking like : "$VAR" or "${VAR1}"
	Useful if you want to look it up and retrieve it's value via getenv.
*/
static char	*retrieve_variable_name(char *variable_substr)
{
	char	*variable_name;
	size_t	i;
	int		braquets;

	if (!variable_substr)
		return (NULL);
	else if (ft_strncmp(variable_substr, "$", 2) == 0)
		return (ft_strdup("$"));
	braquets = 1;
	i = 0;
	if (variable_substr[i] && variable_substr[i] == '$')
		i++;
	if (variable_substr[i] && variable_substr[i] == '{')
	{
		braquets = 3;
		i++;
	}
	variable_name = ft_substr(variable_substr, i,
			ft_strlen(variable_substr) - braquets);
	if (!variable_name)
		return (NULL);
	return (variable_name);
}

/*
	This function replaces the original string by a new one where
	variables have been substituted ($VAR ${VAR}).
	@lens[0] = str's len.
	@lens[1] = substr's len.
	@lens[2] = replacement's len.
*/
char	*substitute_next_string(char *str, const char *substr,
	const char *replacement, size_t *i)
{
	char	*new_str;
	char	*pos;
	size_t	lens[3];

	lens[0] = ft_strlen(str);
	pos = ft_strnstr(str, substr, lens[0]);
	if (!replacement)
		replacement = "";
	if (!pos || !substr)
		return (str);
	lens[1] = ft_strlen(substr);
	lens[2] = ft_strlen(replacement);
	new_str = malloc((lens[0] + (lens[2] - lens[1]) + 1) * sizeof(*new_str));
	if (!new_str)
		return (str);
	ft_memcpy(new_str, str, pos - str);
	ft_memcpy(new_str + (pos - str), replacement, lens[2]);
	ft_memcpy(new_str + (pos - str) + lens[2], pos + lens[1],
		str + lens[0] - (pos + lens[1]));
	new_str[lens[0] + (lens[2] - lens[1])] = '\0';
	(*i) += lens[2];
	free(str);
	return (new_str);
}

char	*substitute_variables(char *line)
{
	char	*variable;
	char	*variable_name;
	char	*env;
	size_t	i;

	if (!line || !*line || !ft_strchr(line, '$'))
		return (line);
	i = 0;
	while (line[i])
	{
		variable = get_next_variable_substr(line, &i);
		if (!variable)
			return (free(line), NULL);
		variable_name = retrieve_variable_name(variable);
		if (!variable_name)
			return (line);
		env = getenv(variable_name);
		if (!env)
			env = variable_name;
		line = substitute_next_string(line, variable, env, &i);
		free(variable);
		free(variable_name);
	}
	return (line);
}
