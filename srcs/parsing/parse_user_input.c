/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_user_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 23:54:01 by nicolas           #+#    #+#             */
/*   Updated: 2023/04/29 14:52:06 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_commands	*parse_user_input(char *line, char ***envp)
{
	t_commands	*commands;

	if (!line)
		return (NULL);
	if (quote_error(line, none))
		return (perror_quote(), free(line), NULL);
	line = substitute_line_content(line, 0, none, envp);
	if (!line)
		return (NULL);
	commands = generate_commands(line, envp);
	if (!commands)
		return (free(line), NULL);
	return (free(line), commands);
}
