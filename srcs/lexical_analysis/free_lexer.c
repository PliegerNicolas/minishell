/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:47:14 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/12 19:48:57 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	free_commands(t_commands *commands)
{
	t_commands	*temp;

	while (commands)
	{
		temp = commands;
		commands = commands->next;
		if (temp->lexer)
			free(temp->lexer);
		free(temp);
	}
}
