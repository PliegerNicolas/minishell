/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:00:10 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/13 00:02:29 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/*
	This is the core function of lexical_analysis. It tries to organise the
	given data and to make sens of it following specific rules :
	=> Commands are separated by semicolons (;)
	=> Lexers are separated by pipes (|). Lexers are inter-communicative
	   commands.
	=> A lexer can take 3 inputs : the executable (exec), the options (defined
	   by letters and preceded by a -) and finally arguments (char **).
	
	@commands : a chained list containing each command. See definition above.
	
	It returns a chained list describing all user's commands.
*/
t_commands	*lexer(char *line)
{
	t_commands	*commands;

	if (!line || !*line)
		return (NULL);
	commands = initialize_commands(line);
	if (!commands)
		return (perror_malloc("@commands (srcs/lexical_analysis/lexer.c #lexer)"), NULL);
	if (fill_commands_lexer(commands, line))
		return (free_commands(commands), NULL);
	return (commands);
}
