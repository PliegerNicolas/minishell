/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 00:24:21 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/12 02:21:31 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	free_2d_str(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	if (arr)
		free(arr);
}

void	free_command(t_command *command)
{
	t_command	*temp_command;

	while (command)
	{
		if (command->exec)
			free(command->exec);
		if (command->options)
			free(command->options);
		if (command->args)
			free_2d_str(command->args);
		temp_command = command;
		command = command->next;
		free(temp_command);
	}
}

void	free_commands(t_command **commands)
{
	int	i;

	i = 0;
	while (commands[i])
		free_command(commands[i++]);
	if (commands)
		free(commands);
}

void	free_parsing_cmd_arr(t_command	*command, char **arr)
{
	free_command(command);
	free_2d_str(arr);
}

void	free_parsing_all(t_command **commands, char **arr)
{
	free_commands(commands);
	free_2d_str(arr);
}
