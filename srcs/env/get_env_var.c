/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 04:31:57 by nicolas           #+#    #+#             */
/*   Updated: 2023/04/05 14:52:10 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*get_env_var(const char *var, const char **envp)
{
	char	*env_var;
	char	**split;
	size_t	i;

	if (!var || !envp)
		return (NULL);
	i = 0;
	while (envp[i] && ft_strncmp(var, envp[i], ft_strlen(var) != 0))
		i++;
	if (!envp[i])
		return (NULL);
	split = ft_setsplit(envp[i], "=");
	if (!split)
		perror_malloc("@split (srcs/parsing/substitute_variables.c #substitute_\
variables)");
	env_var = ft_strdup(split[1]);
	free_str_arr(split);
	if (!env_var)
		return (perror_malloc("@env_var (srcs/env/get_env_var.c #get_env_var)"),
			NULL);
	return (env_var);
}
