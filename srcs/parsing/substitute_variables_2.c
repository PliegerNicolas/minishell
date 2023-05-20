/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_variables_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 13:24:12 by nicolas           #+#    #+#             */
/*   Updated: 2023/05/20 17:59:12 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*replace_escaped_characters(char *line)
{
	char				*substr;
	enum e_quote_status	quote_status;
	enum e_quote_status	mem_quote;
	size_t				i;

	if (!line)
		return (NULL);
	i = 0;
	quote_status = none;
	while (line[i])
	{
		mem_quote = quote_status;
		if (is_between_quotes(line[i], &quote_status) && quote_status != mem_quote)
			i++;
		else if (quote_status == single_quote || line[i] != '\\')
			i++;
		else if (line[i] == '\\' && line[i + 1] && (line[i + 1] == '\'' || line[i + 1] == '\"'))
			i++;
		else if (line[i] == '\\' && line[i + 1] && line[i + 1] != '\\'
			&& quote_status == double_quote)
		{
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
					return (NULL);
			}
			i++;
		}
		else
		{
			substr = ft_substr(line + i, 0, 2);
			if (!substr)
				return (perror_malloc("test6"), free(line), NULL);
			line = replace_first(line, substr, substr + 1);
			if (!line)
				return (NULL);
			i++;
		}
	}
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

/*
static char	*set_env_variable(char *variable_name, char ***envp)
{
	char	*env;
	char	*temp_env;

	if (!variable_name)
		return (NULL);
	if (ft_strncmp(variable_name, "?", 2) == 0)
		env = ft_itoa(g_status);
	else
	{
		temp_env = get_env_var(variable_name, (const char **)*envp);
		if (!temp_env)
			temp_env = ft_strdup("");
		env = temp_env;
	}
	if (!env)
		return (perror_malloc("@env (srcs/parsing/substitute_variables.c #set_e\
nv_variable)"), NULL);
	return (env);
}

static size_t	get_placeholder_len(char *line, size_t i, t_bool brackets)
{
	size_t	len;

	len = 0;
	if (brackets)
		while (line[i + len] && line[i + len] != '}')
			len++;
	else
	{
		while (line[i + len])
		{
			if (len && line[i + len] == '$')
				break ;
			else if (len && line[i + len] == '\\')
				break ;
			else if (ft_isspace(line[i + len]))
				break ;
			else if (line[i + len] == '\'' || line[i + len] == '\"')
				break ;
			len++;
		}
	}
	return (len);
}

char	**set_var_landmarks(char *line, size_t i, t_bool brackets,
	char ***envp)
{
	char	**var_landmarks;
	size_t	len;

	len = get_placeholder_len(line, i, brackets) + 1;
	var_landmarks = ft_calloc(4, sizeof(*var_landmarks));
	if (!var_landmarks)
		return (perror_malloc("@var_landmarks (srcs/parsing/substitute_variable\
s.c #set_var_landmarks)"), NULL);
	var_landmarks[0] = ft_substr(line, i, len - !brackets);
	if (!var_landmarks[0])
		return (perror_malloc("@var_landmarks (srcs/parsing/substitute_variable\
s.c #set_var_landmarks)"), free_str_arr(var_landmarks), NULL);
	var_landmarks[1] = ft_substr(line, i + brackets + 1, len - brackets - 2);
	if (!var_landmarks[1])
		return (perror_malloc("@var_landmarks (srcs/parsing/substitute_variable\
s.c #set_var_landmarks)"), free_str_arr(var_landmarks), NULL);
	var_landmarks[2] = set_env_variable(var_landmarks[1], envp);
	if (!var_landmarks[2])
		return (perror_malloc("@var_landmarks (srcs/parsing/substitute_variable\
s.c #set_var_landmarks)"), free_str_arr(var_landmarks), NULL);
	return (var_landmarks);
}
*/
