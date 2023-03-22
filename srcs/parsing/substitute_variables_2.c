/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_variables_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 13:24:12 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/22 13:25:27 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static char	*set_env_variable(char *variable_name)
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
		return (perror_malloc("@env (srcs/parsing/substitute_variables.c #set_e\
nv_variable)"), NULL);
	return (env);
}


char	**set_variable_landmarks(char *line, size_t i, size_t len,
	t_bool brackets)
{
	char	**variable_landmarks;

	variable_landmarks = ft_calloc(4, sizeof(*variable_landmarks));
	if (!variable_landmarks)
		return (perror_malloc("@variable_landmarks (srcs/parsing/substitute_var\
iables.c #set_variable_landmarks)"), NULL);
	variable_landmarks[0] = ft_substr(line, i, len - !brackets);
	if (!variable_landmarks[0])
		return (perror_malloc("@variable_landmarks (srcs/parsing/substitute_var\
iables.c #set_variable_landmarks)"), free_str_arr(variable_landmarks), NULL);
	variable_landmarks[1] = ft_substr(line, i + brackets + 1, len - brackets - 2);
	if (!variable_landmarks[1])
		return (perror_malloc("@variable_landmarks (srcs/parsing/substitute_var\
iables.c #set_variable_landmarks)"), free_str_arr(variable_landmarks), NULL);
	variable_landmarks[2] = set_env_variable(variable_landmarks[1]);
	if (!variable_landmarks[2])
		return (perror_malloc("@variable_landmarks (srcs/parsing/substitute_var\
iables.c #set_variable_landmarks)"), free_str_arr(variable_landmarks), NULL);
	return (variable_landmarks);
}
