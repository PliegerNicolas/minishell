/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:24:12 by nplieger          #+#    #+#             */
/*   Updated: 2023/03/09 08:44:06 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

enum e_status	g_status = success;

void	prompt(void)
{
	char	*line;

	while (g_status != stop)
	{
		prompt_prefix();
		line = readline(STDIN);
		ft_putendl_fd(line, 1);
		free(line);
	}
}

int	main(int argc, char **argv, char **env)
{
	char				**envp;
	struct sigaction	sa;

	if (argc != 1)
		return (1);
	envp = initialize_env(argc, argv, env);
	if (!envp)
		return (1);
	sa.sa_handler = sighandler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	//signal(SIGINT, sighandler);
	prompt();
	return (free_envp(envp), 0);
}
