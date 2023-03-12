/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_commands.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:51:03 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/12 23:24:07 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static t_commands	*generate_head_commands(size_t *len)
{
	t_commands	*head_commands;

	if (*len)
	{
		(*len)--;
		head_commands = malloc(sizeof(*head_commands));
		if (!head_commands)
		{
			perror_malloc("@head_commands \
(srcs/lexical_analysis/initialize_commands.c #generate_head_commands)");
			return (NULL);
		}
		head_commands->lexer = NULL;
		head_commands->next = NULL;
	}
	return (head_commands);
}

static t_commands	*generate_commands(size_t len)
{
	t_commands	*head_commands;
	t_commands	*commands;

	head_commands = generate_head_commands(&len);
	if (!head_commands)
	{
		perror_malloc("@head_commands \
(srcs/lexical_analysis/initialize_commands.c #generate_commands)");
		return (NULL);
	}
	commands = head_commands;
	while (len--)
	{
		commands->next = malloc(sizeof(*commands));
		if (!commands->next)
		{
			perror_malloc("@commands \
(srcs/lexical_analysis/initialize_commands.c #generate_commands)");
			return (free_commands(head_commands), NULL);
		}
		commands = commands->next;
		commands->lexer = NULL;
		commands->next = NULL;
	}
	return (head_commands);
}

t_commands	*initialize_commands(char *line)
{
	t_commands	*commands;
	size_t		len;

	if (!line || !*line)
		return (NULL);
	len = ft_sections(line, ";");
	commands = generate_commands(len);
	if (!commands)
	{
		perror_malloc("@commands \
(srcs/lexical_analysis/initialize_commands.c #initialize_commands)");
		return (NULL);
	}
	return (commands);
}
