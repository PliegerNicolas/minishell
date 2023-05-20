/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_user_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 23:54:01 by nicolas           #+#    #+#             */
/*   Updated: 2023/05/20 20:32:27 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static t_bool	quote_error(char *line)
{
	size_t				i;
	enum e_quote_status	q_status;
	enum e_quote_status	mem_q;

	if (!line)
		return (FALSE);
	i = 0;
	q_status = none;
	while (line[i])
	{
		mem_q = q_status;
		if (is_between_quotes(line[i], &q_status) && mem_q != q_status)
		{
			i++;
			continue ;
		}
		else if (line[i] == '\\' && line[i + 1] && (line[i + 1] == '\'' || line[i + 1] == '\"'))
			i++;
		i++;
	}
	if (q_status != none)
		return (TRUE);
	return (FALSE);
}

t_commands	*parse_user_input(char *line, char ***envp)
{
	t_commands	*commands;

	if (!line)
		return (NULL);
	if (quote_error(line))
		return (perror_quote(), free(line), NULL);
	line = substitute_line_content(line, 0, none, envp);
	if (!line)
		return (NULL);
	commands = generate_commands(line, envp);
	if (!commands)
		return (free(line), NULL);
	return (free(line), commands);
}
