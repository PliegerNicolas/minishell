/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 22:34:26 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/07 22:36:10 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	put_env(void)
{
	int		i;

	if (!g_envp)
		return ;
	i = 0;
	while (g_envp[i])
	{
		printf("%s\n", g_envp[i]);
		i++;
	}
}

size_t	env_len(char **env)
{
	size_t	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}
