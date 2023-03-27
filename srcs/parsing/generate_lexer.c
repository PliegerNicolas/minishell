/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_lexer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:00:13 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/28 01:37:16 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static t_lexer	*populate_lexer(t_lexer *lexer, const char *cmd,
	enum e_quote_status quote_status)
{
	char	**split;
	int		i;

	if (!lexer)
		return (NULL);
	split = ft_setsplit_quotesafe(cmd, WHITE_SPACES, quote_status);
	if (!split)
		return (free_lexer(lexer), NULL);
	i = 0;
	lexer->exec = get_exec(split[i++]);
	if (!lexer->exec)
		return (free_str_arr(split), free_lexer(lexer), NULL);
	while (split[i] && (ft_isnextcharset(split[i], "-")
			|| ((split[i][0] == '\'' || split[i][0] == '\"')
		&& split[i][1] && ft_isnextcharset(split[i] + 1, "-"))))
		if (get_options(split[i++], &(lexer->options)))
			return (free_str_arr(split), free_lexer(lexer), NULL);
	if (get_arguments((const char **)(split + i), &(lexer->args)))
		return (free_str_arr(split), free_lexer(lexer), NULL);
	return (free_str_arr(split), lexer);
}

static t_lexer	*new_lexer(char *cmd)
{
	t_lexer	*lexer;

	if (!cmd)
		return (NULL);
	lexer = ft_calloc(1, sizeof(*lexer));
	if (!lexer)
		return (perror_malloc("@lexer (srcs/parsing/generate_lexer.c #new_lexer\
)"), NULL);
	lexer = populate_lexer(lexer, cmd, none);
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
	splitted_cmd = ft_setsplit_quotesafe(cmd, "|", none);
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
