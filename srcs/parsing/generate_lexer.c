/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_lexer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:00:13 by nicolas           #+#    #+#             */
/*   Updated: 2023/04/24 15:40:14 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/*
	This function initiazes the values of the linked list element.
	It fills the lexer's variables through the populate_lexer() method.
	It returns the linked list element.
*/
static t_lexer	*new_lexer(char *cmd, size_t id, char ***envp)
{
	t_lexer	*lexer;

	if (!cmd)
		return (NULL);
	lexer = ft_calloc(1, sizeof(*lexer));
	if (!lexer)
		return (perror_malloc("@lexer (srcs/parsing/generate_lexer.c #new_lexer\
)"), NULL);
	lexer->id = id;
	lexer = populate_lexer(lexer, cmd, none, envp);
	if (!lexer)
		return (NULL);
	return (lexer);
}

/*
	This function creates the first element of the lexer linked list.
	Else it adds a new element to the existing linked list.
*/
static t_lexer	*add_lexer(t_lexer *head_lexer, char *cmd, size_t id,
	char ***envp)
{
	t_lexer	*last_lexer;

	if (!head_lexer)
	{
		head_lexer = new_lexer(cmd, id, envp);
		last_lexer = head_lexer;
	}
	else
	{
		last_lexer = head_lexer;
		while (last_lexer->next)
			last_lexer = last_lexer->next;
		last_lexer->next = new_lexer(cmd, id, envp);
		if (last_lexer->next)
			last_lexer->next->previous = last_lexer;
		last_lexer = last_lexer->next;
	}
	if (!last_lexer)
		return (from_lexer_destroy_heredocs(head_lexer),
			free_lexer(head_lexer), NULL);
	return (head_lexer);
}

/*
	This function generates a linked list called lexer.
	Each "command" of the linked list is built on the splitted
	given line, by the "|" character if not placed between quotes.

	This chained list contains the following variables :
	char				*exec;
	char				*options;
	char				**args;
	int					pipefds[2];
	struct s_lexer		*previous;
	struct s_lexer		*next;

	It return's the expected chained_list's head or NULL on error.
*/
t_lexer	*generate_lexer(const char *cmd, char ***envp)
{
	t_lexer	*lexer;
	char	**splitted_cmd;
	int		i;

	if (!cmd)
		return (NULL);
	splitted_cmd = ft_setsplit_quotesafe(cmd, "|", none);
	if (!splitted_cmd)
		return (NULL);
	lexer = NULL;
	i = 0;
	while (splitted_cmd[i])
	{
		lexer = add_lexer(lexer, splitted_cmd[i], i + 1, envp);
		i++;
		if (!lexer)
			return (free_str_arr(splitted_cmd), NULL);
	}
	return (free_str_arr(splitted_cmd), lexer);
}
