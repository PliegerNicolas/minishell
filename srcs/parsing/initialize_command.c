/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 01:14:48 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/12 02:37:34 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_command	*initialize_command(char *line)
{
	t_command	*command;
	char		*trimmed_line;

	if (!line || !*line)
		return (NULL);
	command = malloc(sizeof(*command));
	if (!command)
		return (NULL);
	trimmed_line = ft_strtrim(line, " \t\n\v\f\r");
	if (!trimmed_line)
		return (NULL);
	free(trimmed_line); // temp
	free(command);
	// logique de tri
	return (NULL);
}

static t_command	*generate_commands(char	**split_pipe_line)
{
	t_command	*head_cmd;
	t_command	*command;
	int			i;

	head_cmd = NULL;
	i = 0;
	while (split_pipe_line[i])
	{
		if (!head_cmd)
		{
			head_cmd = initialize_command(split_pipe_line[i++]);
			if (!head_cmd)
				return (free_parsing_cmd_arr(head_cmd, split_pipe_line), NULL);
			command = head_cmd;
		}
		else
		{
			command = command->next;
			command = initialize_command(split_pipe_line[i++]);
			if (!command)
				return (free_parsing_cmd_arr(head_cmd, split_pipe_line), NULL);
		}
		command->next = NULL;
	}
	return (free_2d_str(split_pipe_line), head_cmd);
}

t_command	*initialize_piped_command(char *line)
{
	t_command	*command;
	char		**split_pipe_line;

	if (!line || !*line)
		return (NULL);
	split_pipe_line = ft_split(line, '|');
	if (!split_pipe_line)
		return (NULL);
	command = generate_commands(split_pipe_line);
	if (!command)
		return (NULL);
	return (command);
}
