/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:24:12 by nplieger          #+#    #+#             */
/*   Updated: 2023/03/11 11:56:50 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/*
	This is the core function of the minishell program.
	
	@line : contains what the user gives (supposedly commands).
	@prompt_msg : it's the minishell prefix displayed on console when waiting for
								a command. It's build via the current working directory (cwd).
	@status : it's the status related to the last command (success or failure).
						It has an esthetic purpose. By default the value is success.
	
	It's an infinite loop that exists when line = NULL. Readline returns NULL
	when EOF is met (CTRL+D on empty line).

	- setup_signals() changes how the program should manage certain kind of
		signals (SIGINT & SIGQUIT).
	- rm_echoctl() & reset_echoctl() prevents interrupt messages to be displayed
		in console (^C). 
*/
void	prompt(void)
{
	char			*line;
	char			*prompt_msg;
	enum e_status	status;

	status = success;
	setup_signals();
	rm_echoctl();
	while (1)
	{
		prompt_msg = prompt_prefix(status);
		if (!prompt_msg)
		{
			perror_malloc("prompt_msg (srcs/minishell.c)");
			break ;
		}
		line = readline(prompt_msg);
		free(prompt_msg);
		if (!line)
			break ;
		ft_putendl_fd(line, 1);
		free(line);
		status = success;
	}
	reset_echoctl();
	rl_clear_history();
}

int	main(int argc, char **argv, char **env)
{
	char				**envp;

	if (argc != 1)
		return (perror_minishell_arguments(argc - 1), 1);
	envp = initialize_env(argc, argv, env);
	if (!envp)
		return (perror_environnement_copy(), 1);
	prompt();
	return (free_envp(envp), 0);
}
