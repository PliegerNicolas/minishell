/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:24:12 by nplieger          #+#    #+#             */
/*   Updated: 2023/03/07 23:12:31 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	**g_envp;

void	prompt(void)
{
	char	*line;

	while (1)
	{
		signal(SIGINT, sigint_handler);
		line = readline(0);
		free(line);
	}
	rl_clear_history();
}

int	main(int argc, char **argv, char **env)
{
	if (initialize_env(argc, argv, env))
		return (1);
	prompt();
	return (free_g_envp(), 0);
}
