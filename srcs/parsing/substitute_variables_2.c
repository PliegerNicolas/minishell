/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_variables_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 13:24:12 by nicolas           #+#    #+#             */
/*   Updated: 2023/04/29 14:49:16 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/*
	This function returns the variable's value through the given variable's
	name.
	If the given name is valid but isn't affiliated to a value, it returns
	an empty string.
	On error, it returns NULL.
	The returned variable is always malloced.
*/
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

/*
	Generates a char ** named var_landmarks.
	It contains the following :

	var_landmarks[0] : the variable, '$' char included and potential brackets
					   (placeholder).
	var_landmarks[1] : the variable's name without indicator characters.
	var_landmarks[2] : the variable's value.

	If there is an error, NULL is returned. Else var_landmarks.
*/
char	**set_var_landmarks(char *line, size_t i, size_t len,
	t_bool brackets, char ***envp)
{
	char	**var_landmarks;

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

/*
	This function returns the placeholder's length.
*/
size_t	get_placeholder_len(char *line, size_t i, t_bool brackets)
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
