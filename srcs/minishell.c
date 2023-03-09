/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:24:12 by nplieger          #+#    #+#             */
/*   Updated: 2023/03/09 19:27:10 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

enum e_status	g_status = success;

void	prompt(void)
{
	char	*line;

	while (1)
	{
		prompt_prefix();
		line = readline(" ");
		if (!line)
			break ;
		ft_putendl_fd(line, 1);
		g_status = success;
		free(line);
	}
	rl_clear_history();
}

int	main(int argc, char **argv, char **env)
{
	char				**envp;

	if (argc != 1)
		return (1);
	envp = initialize_env(argc, argv, env);
	if (!envp)
		return (1);
	setup_signals();
	prompt();
	return (free_envp(envp), 0);
}
