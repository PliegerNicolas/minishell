/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_user_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 23:54:01 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/22 17:43:30 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_commands	*parse_user_input(char *line)
{
	t_commands	*commands;

	if (!line)
		return (NULL);
	if (quote_error(line, none))
		return (perror_quote(), free(line), NULL);
	line = substitute_line_content(line, 0, none);
	if (!line)
		return (NULL);
	ft_putendl_fd(line, STDOUT); // temp
	//commands = generate_commands(line);
	//if (!commands)
	//	return (free(line), NULL);
	commands = NULL; // temp
	return (free(line), commands);
}
