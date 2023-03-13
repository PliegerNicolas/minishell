/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_commands.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:51:03 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/13 18:44:11 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/*
	This function trims by whitespace characters the given command. It also
	eliminates strings composed only of whitespace characters.

	@trimmed_cmd is the "returned" str.

	Returns TRUE or FALSE to indicate an error.
	if TRUE, and error has been detected and the program should exit as
	soon as possible.
*/
static t_bool	set_trimmed_command(t_commands **commands,
	const char *cmd, char **trimmed_cmd)
{
	if (!commands || !cmd)
		return (TRUE);
	*trimmed_cmd = ft_strtrim(cmd, " \t\n\v\f\r");
	if (!*trimmed_cmd)
	{
		perror_malloc("@trimmed_cmd (srcs/lexical_analysis/initialize_commands.c #set_trimmed_command)");
		free_commands(*commands);
		*commands = NULL;
		return (TRUE);
	}
	if (ft_strncmp(*trimmed_cmd, "", 1) == 0)
	{
		free(*trimmed_cmd);
		*trimmed_cmd = NULL;
		return (FALSE);
	}
	return (FALSE);
}

/*
	This function populates one element of our commands chained list.
	It populates it's @cmd field. If commands is empty or already
	contains some elements, the new one will be added at the end.

	@commands : the commands chained list we want to populate.
	@last_command : simply a pointer to the last element
					of the commands chained list.

	It returns the newly created element so that it's fields
	can be filled later on. 
*/
static t_commands	*create_command(t_commands **commands)
{
	t_commands	*last_command;

	if (!*commands)
	{
		*commands = malloc(sizeof(**commands));
		if (!*commands)
			return (perror_malloc("@commands (srcs/lexical_analysis/initialize_commands.c #create_command)"), NULL);
		last_command = *commands;
	}
	else
	{
		last_command = *commands;
		while (last_command->next)
			last_command = last_command->next;
		last_command->next = malloc(sizeof(*last_command));
		if (!last_command->next)
		{
			perror_malloc("@last_command->next (srcs/lexical_analysis/initialize_commands.c #create_commands)");
			free_commands(*commands);
			*commands = NULL;
			return (NULL);
		}
		last_command = last_command->next;
	}
	return (last_command);
}

/*
	This function populates one element of the commands chained list.
	Each element of the commands chained list is a command.
	A command is non-full whitespace character string delimited by
	a semicolon(;). If there is no semciolon there one or no
	command.

	@commands : the commands chained list we want to populate.
	@cmd : the str containing the command. It gets whitespace checked
		   and trimmed.
	
	Returns TRUE or FALSE.
	if TRUE, and error has been detected and the program should exit as
	soon as possible.
*/
static t_bool	add_command(t_commands **commands, const char *cmd)
{
	t_commands	*last_command;
	char		*trimmed_cmd;

	if (!cmd)
		return (TRUE);
	if (set_trimmed_command(commands, cmd, &trimmed_cmd))
		return (TRUE);
	else if (!trimmed_cmd)
		return (FALSE);
	last_command = create_command(commands);
	if (!last_command)
		return (free(trimmed_cmd), TRUE);
	last_command->cmd = trimmed_cmd;
	last_command->lexer = NULL;
	last_command->next = NULL;
	return (FALSE);
}

/*
	This function initializes the commands chained list.
	Each element of the commands chained list contains :
	- @cmd : a trimmed and not only whitespace string, delimited
	  by a semicolon (;) from the user input
	- @lexer : a struct that decomposes the role of each
	  part (delimited by whitespace characters) of the @cmd variable.
	
	@commands_str : the splitted user's input by semicolon (;).
	@commands : the commands chained list.

	- add_command() : adds an element at the end of the @commands variable.

	Returns the commands chained list, a.k.a the formatted user's input.
*/
t_commands	*initialize_commands(const char **commands_str)
{
	t_commands	*commands;
	int			i;

	if (!commands_str)
		return (NULL);
	commands = NULL;
	i = 0;
	while (commands_str[i])
		if (add_command(&commands, commands_str[i++]))
			return (NULL);
	return (commands);
}
