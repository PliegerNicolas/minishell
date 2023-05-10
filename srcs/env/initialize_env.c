/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 21:38:17 by nicolas           #+#    #+#             */
/*   Updated: 2023/05/10 16:06:27 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static char	**set_default_envp_var(char *name, char *value, char **envp)
{
	char	*temp;

	temp = get_env_var(name, (const char **)envp);
	if (!temp)
	{
		envp = set_env_var(name, value, envp);
		if (!envp)
			return (NULL);
	}
	else
		free(temp);
	return (envp);
}

char	**set_default_envp_values(char **envp)
{
	if (!envp)
		return (NULL);
	envp = set_default_envp_var("SHLVL", "1", envp);
	if (!envp)
		return (NULL);
	envp = set_default_envp_var("_", "/usr/bin/env", envp);
	if (!envp)
		return (NULL);
	return (envp);
}

/*
	This copies the inhereted env (environnement) variable to a pointer
	so it can freely be used and modified.
*/
char	**initialize_env(int argc, char **argv, char **env)
{
	char	**envp;
	int		i;

	envp = malloc((env_len(env) + 1) * sizeof(*envp));
	if (!envp)
		return (NULL);
	i = 0;
	while (env[i])
	{
		envp[i] = ft_strdup(env[i]);
		if (!envp[i])
			return (free_envp(envp), NULL);
		i++;
	}
	envp[i] = 0;
	envp = set_default_envp_values(envp);
	(void)argc;
	(void)argv;
	return (envp);
}
