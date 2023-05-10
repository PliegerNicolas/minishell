/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:24:12 by nplieger          #+#    #+#             */
/*   Updated: 2023/05/10 15:19:44 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

enum e_status	g_status = success;

/*
	- setup_signals() changes how the program should manage certain kind of
		signals (SIGINT, SIGQUIT & SIGTSTP).
	- rm_echoctl() prevents interrupt messages to be displayed
		in console (example : ^C). 
*/
static void	prompt_init(void)
{
	setup_signals();
	rm_echoctl();
}

/*
	- reset_echoctl() removes all modifications done by rm_echoctl().
	- rl_clear_history() clears readline's history.
*/
static void	prompt_exit(void)
{
	rl_clear_history();
	reset_echoctl();
	reset_signals();
}

/*
	This is the core of the minishell program.
	
	@line : contains what the user gives (supposedly commands).
	@prompt_msg : it's the minishell prefix displayed on console when waiting for
								a command. It's build via the current working directory (cwd).
	@status : it's the status related to the last command (success or failure).
						It has an esthetic purpose. By default the value is success.
	
	It's an infinite loop that exists when line = NULL. Readline returns NULL
	when EOF is met (CTRL+D on empty line).
*/
static void	prompt(char ***envp)
{
	char			*line;
	char			*prompt_msg;

	while (g_status != exit_program)
	{
		prompt_msg = prompt_prefix(envp);
		if (!prompt_msg)
			break ;
		line = readline(prompt_msg);
		free(prompt_msg);
		if (!line)
			break ;
		if (ft_only_whitespace(line))
		{
			free(line);
			continue ;
		}
		add_history(line);
		g_status = executer(envp, line);
	}
}

/*
	@envp : it stores the passed env in a stack pointer so it
			can be more freely handled later.
	@argc : number of given arguments. We want none.
	@argv : arguments as strings. We want none.

	- prompt_init() : some configuration (signals and default bash behavior)
	- prompt() : enters the core function of the program.
	- prompt_exit() : clears readline's history and resets
						everything done by prompt_init().
*/
int	main(int argc, char **argv, char **env)
{
	char				**envp;

	if (argc != 1)
		return (perror_minishell_arguments(argc - 1), close_stds(), 1);
	envp = initialize_env(argc, argv, env);
	if (!envp)
		return (perror_environnement(), close_stds(), 1);
	prompt_init();
	prompt(&envp);
	prompt_exit();
	return (free_envp(envp), close_stds(), 0);
}
