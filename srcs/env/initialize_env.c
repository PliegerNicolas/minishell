/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 21:38:17 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/08 18:33:56 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	**initialize_env(int argc, char **argv, char **env)
{
	char	**envp;
	int		i;

	envp = ft_calloc((env_len(env) + 1), sizeof(*envp));
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
	(void)argc;
	(void)argv;
	return (envp);
}
