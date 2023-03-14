/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 00:02:51 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/13 22:59:03 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/*
	This is the core function once the user's input has been read.
	First it parses/lexers it.
	Then it finds and executes commands following user's input.
	
	@commands : a chained list containing parsed data. Each element of this list
				is a command. Each command (options, arguments, pipes, ...) is
				separated by semicolons (;).
	- set_commands(line) : this function treat's user's input.
	- ???

	It returns the command's status (success / failure).
*/
enum e_status	exec(char **envp, char *line)
{
	t_commands	*commands;

	if (!*line)
		return (failure);
	commands = set_commands(line);
	if (!commands)
		return (perror_malloc("@commands (srcs/execution/exec.c #exec)"), failure);
	// execute commands
	(void)envp;
	return (free_commands(commands), success);
}
