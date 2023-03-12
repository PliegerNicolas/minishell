/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:47:14 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/12 23:38:46 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

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
	This function frees t_commands. A chained
*/
void	free_commands(t_commands *commands)
{
	t_commands	*temp;

	while (commands)
	{
		temp = commands;
		commands = commands->next;
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
