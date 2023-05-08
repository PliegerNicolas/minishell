/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 04:31:57 by nicolas           #+#    #+#             */
/*   Updated: 2023/05/08 15:32:54 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	ft_envp_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t		i;

	i = 0;

	while ((s1[i] || s2[i]) && s2[i] != '=')
	{
		if (s1[i] != s2[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	if (i != n)
		return (-1);
	return (0);
}

char	*get_env_var(const char *var, const char **envp)
{
	char	*env_var;
	char	**split;
	size_t	i;

	if (!var || !envp)
		return (NULL);
	i = 0;
	while (envp[i] && ft_envp_strncmp(var, envp[i], ft_strlen(var)) != 0)
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
