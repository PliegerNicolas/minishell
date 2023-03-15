/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_variables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 00:02:15 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/15 17:02:05 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/*
	Returns a malloced string containing the first variable.
	Examples : "${VAR}" or "$VAR".
	It also moves the cursor (i) around so multiple variables can be read
	through a while loop.
*/
static char	*get_next_variable_substr(char *line, size_t *i)
{
	char	*variable_substr;
	int		braquets;
	int		start;
	int		len;

	if (!line || !line[*i])
		return (NULL);
	while (line[*i] && line[*i] != '$')
		(*i)++;
	if (!line[*i])
		return (NULL);
	braquets = 1;
	start = *i;
	len = 0;
	while (line[*i + len] && !ft_isspace(line[*i + len]) && braquets != 0)
	{
		if (line[*i + len] == '{')
			braquets++;
		else if (line[*i + len] == '}')
			if (--braquets == 1)
				braquets--;
		len++;
	}
	variable_substr = ft_substr(line, start, len);
	return (variable_substr);
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
	braquets = 1;
	i = 1;
	if (variable_substr[i] == '{')
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
void	substitute_next_string(char **str, const char *substr,
	const char *replacement, size_t *i)
{
	char	*new_str;
	char	*pos;
	size_t	lens[3];

	lens[0] = ft_strlen(*str);
	pos = ft_strnstr(*str, substr, lens[0]);
	if (!replacement)
		replacement = "";
	if (!pos || !substr)
		return ;
	lens[1] = ft_strlen(substr);
	lens[2] = ft_strlen(replacement);
	new_str = malloc((lens[0] + (lens[2] - lens[1]) + 1) * sizeof(*new_str));
	if (!new_str)
		return ;
	ft_memcpy(new_str, *str, pos - *str);
	ft_memcpy(new_str + (pos - *str), replacement, lens[2]);
	ft_memcpy(new_str + (pos - *str) + lens[2], pos + lens[1],
		*str + lens[0] - (pos + lens[1]));
	new_str[lens[0] + (lens[2] - lens[1])] = '\0';
	(*i) += lens[2];
	free(*str);
	*str = new_str;
}

void	substitute_variables(char **line)
{
	char	*variable;
	char	*variable_name;
	char	*env;
	size_t	i;

	if (!line || !*line || !ft_strchr(*line, '$'))
		return ;
	i = 0;
	while (line[i])
	{
		variable = get_next_variable_substr(*line, &i);
		if (!variable)
			return ;
		variable_name = retrieve_variable_name(variable);
		if (!variable_name)
		{
			free(variable);
			return ;
		}
		env = getenv(variable_name);
		substitute_next_string(line, variable, env, &i);
		free(variable);
		free(variable_name);
	}
}
