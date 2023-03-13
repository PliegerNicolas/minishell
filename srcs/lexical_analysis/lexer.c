/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:00:10 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/13 19:06:11 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	str_arr_len(const char **str_arr)
{
	int		i;

	i = 0;
	if (!cmd)
		return (i);
	while (str_arr[i])
		i++;
	return (i);
}

static t_lexer	*initialize_lexer(char *cmd)
{
	t_lexer	*lexer;
	char	**splitted_cmd;
	int		len;

	if (!cmd)
		return (NULL);
	splitted_cmd = ft_split(cmd, ' ');
	if (!splitted_cmd)
		return (NULL);
	lexer = malloc(sizeof(*lexer));
	if (!lexer)
	{
		perror_malloc("@lexer (srcs/lexical_analysis/lexer.c #initialize_lexers)");
		return (free_str_arr(splitted_cmd), NULL);
	}
	//

	//
	free_str_arr(splitted_cmd);
	return (lexer);
}

static t_commands	*fill_lexers(t_commands *commands)
{
	t_commands	*current_command;

	if (!commands)
		return (NULL);
	current_command = commands;
	while (current_command)
	{
		current_command->lexer = initialize_lexer(current_command->cmd);
		if (!current_command->lexer)
		{
			perror_malloc("@current_command->lexer (srcs/lexical_analysis/lexer.c #fill_lexers)");
			return (free_commands(commands), NULL);
		}
		current_command = current_command->next;
	}
	return (commands);
}

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
	char		**commands_str;

	if (!line || !*line)
		return (NULL);
	commands_str = ft_split(line, ';');
	if (!commands_str)
		return (NULL);
	commands = initialize_commands((const char **)commands_str);
	free_str_arr(commands_str);
	// fill lexer
	if (!commands)
		return (perror_malloc("@commands (srcs/lexical_analysis/lexer.c #lexer)"), NULL);
	return (commands);
}
