/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 23:30:48 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/26 14:02:28 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static t_commands	*new_command(char *cmd)
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
	command->lexer = generate_lexer(command->cmd);
	if (!command->lexer)
		return (free_commands(command), NULL);
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
	splitted_line = ft_setsplit_quotesafe(line, ";", none);
	if (!splitted_line)
		return (perror_malloc("@splitted_line (srcs/parsing/generate_commands.c\
#generate_commands)"), NULL);
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
