/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 00:02:51 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/28 03:00:45 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

enum e_status	executer(char **envp, char *line)
{
	t_commands	*commands;

	if (!line || !envp)
		return (free(line), general_failure);
	if (!*line)
		return (free(line), success);
	commands = parse_user_input(line);
	if (!commands)
		return (general_failure);
	// execute commands
	// temp
	if (commands->lexer->exec)
		printf("%s\n", commands->lexer->exec);
	if (commands->lexer->options)
		printf("%s\n", commands->lexer->options);
	if (commands->lexer->args && commands->lexer->args[0])
		printf("%s\n", commands->lexer->args[0]);
	if (commands->lexer->args && commands->lexer->args[1])
		printf("%s\n", commands->lexer->args[1]);
	if (commands->lexer->args && commands->lexer->args[2])
		printf("%s\n", commands->lexer->args[2]);
	// temp
	return (free_commands(commands), success);
}
