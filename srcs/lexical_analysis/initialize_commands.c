/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_commands.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:51:03 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/13 00:11:03 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/*
	This function exists because of the 42 norm. It generates the head of
	the commands chained list. See below functions for more info.

	It returns the head of the commands chained list.
*/
static t_commands	*generate_head_commands(size_t *len)
{
	t_commands	*head_commands;

	*head_commands = NULL;
	if (*len)
	{
		(*len)--;
		head_commands = malloc(sizeof(*head_commands));
		if (!head_commands)
			return (perror_malloc("@head_commands (srcs/lexical_analysis/initialize_commands.c #generate_head_commands)"), NULL);
		head_commands->lexer = NULL;
		head_commands->next = NULL;
	}
	return (head_commands);
}

/*
	This function Generated for each section of the given line a
	spot in the commands's chained list.

	It initializes all lexers to NULL.

	- generate_head_commands() : a simple function to generate the head of the list.
	  It exists just because of the 42 norm.

	It returns the head of the commands chained list.
*/
static t_commands	*generate_commands(size_t len)
{
	t_commands	*head_commands;
	t_commands	*commands;

	head_commands = generate_head_commands(&len);
	if (!head_commands)
		return (perror_malloc("@head_commands (srcs/lexical_analysis/initialize_commands.c #generate_commands)"), NULL);
	commands = head_commands;
	while (len--)
	{
		commands->next = malloc(sizeof(*commands));
		if (!commands->next)
		{
			perror_malloc("@commands (srcs/lexical_analysis/initialize_commands.c #generate_commands)");
			return (free_commands(head_commands), NULL);
		}
		commands = commands->next;
		commands->lexer = NULL;
		commands->next = NULL;
	}
	return (head_commands);
}

/*
	Initializes the commands (chained list). It doesn't initialize
	lexers : see "fill_commands_lexer.c".
	
	@commands : A chained list containing each "command". Each command
				is separated by a semicolon (;). If there is no
				semicolon (;), there is only one or zero command.
	@len : Detected potential "commands". Aka number of elements
		   in commands chained list.

	It returns the command's chained_list. Lexers aren't initialized yet.
*/
t_commands	*initialize_commands(char *line)
{
	t_commands	*commands;
	size_t		len;

	if (!line || !*line)
		return (NULL);
	len = ft_sections(line, ";");
	commands = generate_commands(len);
	if (!commands)
		return (perror_malloc("@commands (srcs/lexical_analysis/initialize_commands.c #initialize_commands)"), NULL);
	return (commands);
}
