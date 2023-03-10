/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:24:12 by nplieger          #+#    #+#             */
/*   Updated: 2023/03/10 13:44:38 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/*
	The core of the minishell program.
	- An infinite loop that can be exited by pressing CTRL+D when STDIN
	is empty (readline returns NULL).
	- setup_signals() : Modifies the behaviour on reception of certain signals.
	- readline(" ") : the space prevents deleting the prompt prefix.
*/
void	prompt(void)
{
	char			*line;
	char			*prompt_msg;
	enum e_status	status;

	status = success;
	setup_signals();
	prompt_msg = NULL;
	while (1)
	{
		prompt_msg = prompt_prefix(status);
		if (!prompt_msg)
			break ;
		line = readline(prompt_msg);
		free(prompt_msg);
		if (!line)
			break ;
		ft_putendl_fd(line, 1);
		free(line);
		status = success;
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
	prompt();
	return (free_envp(envp), 0);
}
