/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_user_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 23:54:01 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/20 13:30:35 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_commands	*parse_user_input(char *line)
{
	t_commands	*commands;

	if (!line)
		return (NULL);
	line = substitute_variables(line, 0);
	if (!line)
		return (NULL);
	ft_putendl_fd(line, STDOUT); // temp
	commands = generate_commands(line);
	if (!commands)
		return (free(line), NULL);
	return (free(line), commands);
}
