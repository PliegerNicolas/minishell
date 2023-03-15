/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_user_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 23:54:01 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/15 16:35:27 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_commands	*parse_user_input(char *line)
{
	t_commands	*commands;

	if (!line)
		return (NULL);
	line = substitute_variables(line);
	if (line)
		printf("%s\n", line);
	// subtitute line
	// generate commands
	commands = NULL; // temp
	return (commands);
}
