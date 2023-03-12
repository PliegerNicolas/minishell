/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 00:01:27 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/12 02:13:50 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_command	**parse(char *line)
{
	t_command	**commands;
	char		**split_semcol_line;
	int			i;

	if (!line || !*line)
		return (NULL);
	split_semcol_line = ft_split(line, ';');
	if (!split_semcol_line)
		return (NULL);
	commands = malloc((ft_2d_strlen((const char **)split_semcol_line) + 1)
			* sizeof(**commands));
	if (!commands)
		return (free_2d_str(split_semcol_line), NULL);
	i = 0;
	while (split_semcol_line[i])
	{
		commands[i] = initialize_piped_command(split_semcol_line[i]);
		if (!commands[i])
			return (free_parsing_all(commands, split_semcol_line), NULL);
		i++;
	}
	commands[i] = NULL;
	free_2d_str(split_semcol_line);
	return (commands);
}
