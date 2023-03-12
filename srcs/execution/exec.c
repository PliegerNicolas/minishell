/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 00:02:51 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/12 23:33:10 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

enum e_status	exec(char **envp, char *line)
{
	t_commands	*commands;

	if (!*line)
		return (failure);
	commands = lexer(line);
	if (!commands)
		return (perror_malloc("@commands \
(srcs/execution/exec.c #exec)"), failure);
	(void)envp;
	// execute commands.
	// free commands.
	return (free_commands(commands), success);
}
