/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_user_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 23:54:01 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/19 12:44:53 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_commands	*parse_user_input(char *line)
{
	t_commands	*commands;

	if (!line)
		return (NULL);
	/*
	line = substitute_variables(line);
	if (!line)
		return (free(line), NULL);
	*/
	line = substitute_variables(line, 0);
	if (!line)
		return (NULL);
	if (line) // temp
		ft_putendl_fd(line, STDOUT); // temp
	commands = generate_commands(line);
	return (free(line), commands);
}
