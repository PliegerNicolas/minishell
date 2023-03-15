/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_user_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 23:54:01 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/15 23:46:56 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_commands	*parse_user_input(char **line)
{
	t_commands	*commands;

	if (!*line)
		return (NULL);
	substitute_variables(line);
	if (*line) // temp
		ft_putendl_fd(*line, STDOUT); // temp
	commands = generate_commands(*line);
	return (commands);
}
