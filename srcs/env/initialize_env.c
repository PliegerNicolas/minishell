/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 21:38:17 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/07 22:37:07 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_bool	initialize_env(char **env)
{
	int		i;

	g_envp = ft_calloc((env_len(env) + 1), sizeof(char *));
	if (!g_envp)
		return (TRUE);
	i = 0;
	while (env[i])
	{
		g_envp[i] = ft_strdup(env[i]);
		if (!g_envp[i])
		{
			free_g_envp();
			return (TRUE);
		}
		i++;
	}
	g_envp[i] = 0;
	return (FALSE);
}
