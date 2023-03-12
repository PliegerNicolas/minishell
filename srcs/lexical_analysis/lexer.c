/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:00:10 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/12 19:51:38 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_commands	*lexer(char *line)
{
	t_commands	*commands;

	if (!line || !*line)
		return (NULL);
	commands = initialize_commands(line);
	return (commands);
}
