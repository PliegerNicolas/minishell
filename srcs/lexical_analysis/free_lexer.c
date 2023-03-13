/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:47:14 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/13 18:03:07 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/*
	This function free char** variables.
	Practical in case of usage of these following functions or variables :
	- @lexer->args or commands->lexer->args;
	- ft_split();
*/
void	free_str_arr(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	if (arr)
		free(arr);
}

/*
	This function frees t_commands.
	t_commands is a chained list containing every "command" given by the user.
	A command is considered as a string finished by a semicolon (;). If no
	semicolon (;) is given and the string exists, there is one command.
*/
void	free_commands(t_commands *commands)
{
	t_commands	*temp;

	while (commands)
	{
		temp = commands;
		commands = commands->next;
		if (temp->cmd)
			free(temp->cmd);
		if (temp->lexer)
		{
			if (temp->lexer->exec)
				free(temp->lexer->exec);
			if (temp->lexer->options)
				free(temp->lexer->options);
			if (temp->lexer->args)
				free_str_arr(temp->lexer->args);
			free(temp->lexer);
		}
		free(temp);
	}
}
