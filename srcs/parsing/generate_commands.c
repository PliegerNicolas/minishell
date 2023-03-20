/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 23:30:48 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/20 14:30:20 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static t_commands	*new_command(char *cmd)
{
	t_commands	*command;

	if (!cmd)
		return (NULL);
	command = malloc(sizeof(*command));
	if (!command)
	{
		perror_malloc("@command \
(srcs/parsing/generate_commands.c #new_command");
		return (NULL);
	}
	command->cmd = ft_strtrim(cmd, " ");
	if (!command->cmd)
	{
		perror_malloc("@command->cmd \
(srcs/parsing/generate_commands.c #new_command");
		free(command);
		return (NULL);
	}
	command->lexer = NULL; // temp
	command->next = NULL;
	return (command);
}

static t_commands	*add_command(t_commands *head_command, char *cmd)
{
	t_commands	*last_command;

	if (!head_command)
	{
		head_command = new_command(cmd);
		last_command = head_command;
	}
	else
	{
		last_command = head_command;
		while (last_command->next)
			last_command = last_command->next;
		last_command->next = new_command(cmd);
		last_command = last_command->next;
	}
	if (!last_command)
		return (free_commands(head_command), NULL);
	return (head_command);
}

t_commands	*generate_commands(const char *line)
{
	t_commands	*commands;
	char		**splitted_line;
	int			i;

	if (!line || !*line)
		return (NULL);
	splitted_line = ft_setsplit_quotesafe(line, ";");
	if (!splitted_line)
	{
		perror_malloc("@splitted_line \
(srcs/parsing/generate_commands.c #generate_commands)");
		return (NULL);
	}
	i = 0;
	commands = NULL;
	while (splitted_line[i])
	{
		commands = add_command(commands, splitted_line[i++]);
		if (!commands)
			return (free_str_arr(splitted_line), NULL);
	}
	return (free_str_arr(splitted_line), commands);
}
