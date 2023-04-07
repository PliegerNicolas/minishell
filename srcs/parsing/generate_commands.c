/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 23:30:48 by nicolas           #+#    #+#             */
/*   Updated: 2023/04/08 01:38:42 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/*
	This function initiazes the values of the linked list element.
	It trims the given line and stores it and builds a lexer through the
	trimmed line.
	It returns the linked list command.
*/
static t_commands	*new_command(char *cmd, char ***envp)
{
	t_commands	*command;

	if (!cmd)
		return (NULL);
	command = ft_calloc(1, sizeof(*command));
	if (!command)
		return (perror_malloc("@command (srcs/parsing/generate_commands.c #new_\
command"), NULL);
	command->cmd = ft_strtrim(cmd, WHITE_SPACES);
	if (!command->cmd)
		return (perror_malloc("@command->cmd (srcs/parsing/generate_commands.c \
#new_command"), free_commands(command), NULL);
	command->lexer = generate_lexer(command->cmd, envp);
	if (!command->lexer)
		return (free_commands(command), NULL);
	return (command);
}

/*
	This function creates the first element of the command linked list.
	Else it adds a new element to the existing linked list.
*/
static t_commands	*add_command(t_commands *head_command, char *cmd,
	char ***envp)
{
	t_commands	*last_command;

	if (!head_command)
	{
		head_command = new_command(cmd, envp);
		last_command = head_command;
	}
	else
	{
		last_command = head_command;
		while (last_command->next)
			last_command = last_command->next;
		last_command->next = new_command(cmd, envp);
		last_command = last_command->next;
	}
	if (!last_command)
		return (free_commands(head_command), NULL);
	return (head_command);
}

/*
	This function generates a linked list called commands.
	Each "command" of the linked list is built on the splitted
	given line, by the ";" character if not placed between quotes.

	This chained list contains the following variables :
	char				*cmd;
	t_lexer				*lexer;
	struct s_commands	*next;

	It return's the expected chained_list's head or NULL on error.
*/
t_commands	*generate_commands(const char *line, char ***envp)
{
	t_commands	*commands;
	char		**splitted_line;
	int			i;

	if (!line || !*line)
		return (NULL);
	splitted_line = ft_setsplit_quotesafe(line, ";", none);
	if (!splitted_line)
		return (perror_malloc("@splitted_line (srcs/parsing/generate_commands.c\
#generate_commands)"), NULL);
	i = 0;
	commands = NULL;
	while (splitted_line[i])
	{
		commands = add_command(commands, splitted_line[i++], envp);
		if (!commands)
			return (free_str_arr(splitted_line), NULL);
	}
	return (free_str_arr(splitted_line), commands);
}
