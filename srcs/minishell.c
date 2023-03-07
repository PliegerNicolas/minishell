/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:24:12 by nplieger          #+#    #+#             */
/*   Updated: 2023/03/07 23:18:40 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	**g_envp;

void	prompt(void)
{
	char	*line;

	while (1)
	{
		line = readline(0);
		free(line);
		break ;
	}
}

int	main(int argc, char **argv, char **env)
{
	if (initialize_env(argc, argv, env))
		return (1);
	prompt();
	return (free_g_envp(), 0);
}
