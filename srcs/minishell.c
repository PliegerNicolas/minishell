/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:24:12 by nplieger          #+#    #+#             */
/*   Updated: 2023/03/08 18:36:57 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

enum e_status	g_status = success;

void	prompt(void)
{
	char	*line;

	while (g_status != stop)
	{
		line = readline(0);
		free(line);
		g_status = stop;
	}
}

int	main(int argc, char **argv, char **env)
{
	char	**envp;

	if (argc != 1)
		return (1);
	envp = initialize_env(argc, argv, env);
	if (!envp)
		return (1);
	prompt();
	return (free_envp(envp), 0);
}
