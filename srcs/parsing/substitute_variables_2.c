/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_variables_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 13:24:12 by nicolas           #+#    #+#             */
/*   Updated: 2023/05/20 20:11:06 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*replace_escaped_characters_double_quotes(char *line, size_t i)
{
	char	*substr;

	substr = ft_substr(line + i, 0, 2);
	if (!substr)
		return (perror_malloc("test5"), free(line), NULL);
	if (ft_strncmp(line + i, "\\n", 2) == 0)
		line = replace_first(line, substr, "\n");
	else if (ft_strncmp(line + i, "\\t", 2) == 0)
		line = replace_first(line, substr, "\t");
	else if (ft_strncmp(line + i, "\\v", 2) == 0)
		line = replace_first(line, substr, "\v");
	else if (ft_strncmp(line + i, "\\f", 2) == 0)
		line = replace_first(line, substr, "\f");
	else if (ft_strncmp(line + i, "\\r", 2) == 0)
		line = replace_first(line, substr, "\r");
	else
	{
		line = replace_first(line, substr, substr + 1);
		if (!line)
			return (free(substr), NULL);
	}
	return (free(substr), line);
}

static char	*replace_escaped_characters_other(char *line, size_t i)
{
	char	*substr;

	substr = ft_substr(line + i++, 0, 2);
	if (!substr)
		return (perror_malloc("test6"), free(line), NULL);
	line = replace_first(line, substr, substr + 1);
	free(substr);
	if (!line)
		return (NULL);
	return (line);
}

char	*replace_escaped_characters(char *line, size_t i,
	enum e_quote_status q_status)
{
	enum e_quote_status	mem_q;

	while (line && line[i])
	{
		mem_q = q_status;
		if ((is_between_quotes(line[i], &q_status) && q_status != mem_q)
			|| q_status == single_quote || line[i] != '\\')
			i++;
		else if (line[i] == '\\' && line[i + 1])
		{
			if (is_inset(line[i + 1], "\'\""))
				i++;
			else if (/*line[i + 1] != '\\' && */q_status == double_quote)
				line = replace_escaped_characters_double_quotes(line, i);
			i++;
		}
		else
			line = replace_escaped_characters_other(line, i++);
	}
	if (!line)
		return (NULL);
	return (line);
}

char	*find_variable_value(char *line, size_t j, char ***envp)
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
		return (perror_malloc("@variable_name (srcs/parsing/substitute_variable\
s_1.c #find_variable_value)"), NULL);
	variable_value = get_env_var(variable_name, (const char **)*envp);
	free(variable_name);
	if (!variable_value)
		variable_value = ft_strdup("");
	if (!variable_value)
		return (perror_malloc("@variable_value (srcs/parsing/substitute_variabl\
es_1.c #find_variable_value)"), NULL);
	return (variable_value);
}
