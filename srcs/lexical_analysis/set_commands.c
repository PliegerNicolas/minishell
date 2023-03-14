/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 22:59:15 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/14 16:19:24 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static t_commands	*initialize_head_command(t_commands *head_command, char *cmd)
{
	if (!cmd)
		return (NULL);
	if (head_command)
		return (head_command);
	head_command = malloc(sizeof(*head_command));
	if (!head_command)
	{
		perror_malloc("@head_command (srcs/lexical_analysis/set_commands.c #initialize_head_command)");
		return (NULL);
	}
	head_command->cmd = ft_strtrim(cmd, WHITE_SPACES);
	head_command->lexer = NULL;
	head_command->next = NULL;
	return (head_command);
}

static t_commands	*initialize_command(t_commands *head_command, char *cmd)
{
	t_commands	*command;

	if (!head_command)
		return (NULL);
	command = head_command;
	while (command->next)
		command = command->next;
	command->next = malloc(sizeof(*command));
	if (!command->next)
	{
		perror_malloc("@command->next (srcs/lexical_analysis/set_commands.c #initialize_command)");
		return (free_commands(head_command), NULL);
	}
	command = command->next;
	command->cmd = ft_strtrim(cmd, WHITE_SPACES);
	command->lexer = NULL;
	command->next = NULL;
	return (head_command);
}

static t_commands	*initialize_commands(char **splitted_commands)
{
	t_commands	*commands;
	int			i;

	if (!splitted_commands || !*splitted_commands)
		return (NULL);
	i = 0;
	commands = NULL;
	commands = initialize_head_command(commands, splitted_commands[i++]);
	if (!commands)
		return (NULL);
	while (splitted_commands[i])
	{
		commands = initialize_command(commands, splitted_commands[i++]);
		if (!commands)
			return (NULL);
	}
	return (commands);
}

t_commands	*set_commands(const char *line)
{
	char		**splitted_commands;
	t_commands	*commands;

	if (!line)
		return (NULL);
	splitted_commands = ft_split_by_set_quote_safe(line, ";");
	if (!splitted_commands)
	{
		perror_malloc("@splitted_commands (srcs/lexical_analysis/set_commands.c #set_commands)");
		return (NULL);
	}
	commands = initialize_commands(splitted_commands);
	if (!commands)
	{
		perror_malloc("@commands (srcs/lexical_analysis/set_commands.c #set_commands)");
		return (free_str_arr(splitted_commands), NULL);
	}
	return (free_str_arr(splitted_commands), commands);
}
