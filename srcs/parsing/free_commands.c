/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 23:58:54 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/31 16:42:38 by nicolas          ###   ########.fr       */
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

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

/*
	This function frees all elements of a lexer struct.
	A lexer structure contains arranged data based on
	user input.
*/
void	free_lexer(t_lexer *lexer)
{
	t_lexer	*temp;

	if (!lexer)
		return ;
	while (lexer)
	{
		temp = lexer;
		lexer = lexer->next;
		if (temp->cmd)
			free(temp->cmd);
		if (temp->exec)
			free(temp->exec);
		if (temp->options)
			free(temp->options);
		if (temp->redir_str)
			free(temp->redir_str);
		if (temp->args)
			free_str_arr(temp->args);
		free(temp);
	}
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
			free_lexer(temp->lexer);
		free(temp);
	}
}
