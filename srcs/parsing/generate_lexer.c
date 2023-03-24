/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_lexer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:00:13 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/24 13:26:13 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static t_lexer	*new_lexer(char *cmd)
{
	t_lexer	*lexer;

	if (!cmd)
		return (NULL);
	lexer = ft_calloc(1, sizeof(*lexer));
	if (!lexer)
	{
		perror_malloc("@lexer (srcs/parsing/generate_lexer.c #new_lexer)");
		return (NULL);
	}
	lexer = populate_lexer(lexer, cmd, 0);
	if (!lexer)
		return (NULL);
	return (lexer);
}

static t_lexer	*add_lexer(t_lexer *head_lexer, char *cmd)
{
	t_lexer	*last_lexer;

	if (!head_lexer)
	{
		head_lexer = new_lexer(cmd);
		last_lexer = head_lexer;
	}
	else
	{
		last_lexer = head_lexer;
		while (last_lexer->next)
			last_lexer = last_lexer->next;
		last_lexer->next = new_lexer(cmd);
		last_lexer->next->previous = last_lexer;
		last_lexer = last_lexer->next;
	}
	if (!last_lexer)
		return (free_lexer(head_lexer), NULL);
	return (head_lexer);
}

t_lexer	*generate_lexer(const char *cmd)
{
	t_lexer	*lexer;
	char	**splitted_cmd;
	int		i;

	if (!cmd)
		return (NULL);
	splitted_cmd = ft_setsplit(cmd, "|");
	if (!splitted_cmd)
		return (NULL);
	lexer = NULL;
	i = 0;
	while (splitted_cmd[i])
	{
		lexer = add_lexer(lexer, splitted_cmd[i++]);
		if (!lexer)
			return (free_str_arr(splitted_cmd), NULL);
	}
	return (free_str_arr(splitted_cmd), lexer);
}
