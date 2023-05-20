/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:17:40 by nicolas           #+#    #+#             */
/*   Updated: 2023/05/21 00:13:02 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static size_t	quoteless_len(char *line, enum e_quote_status q_status)
{
	size_t				i;
	size_t				len;
	enum e_quote_status	mem_q;

	i = 0;
	len = 0;
	while (line && line[i])
	{
		mem_q = q_status;
		if (is_between_quotes(line[i], &q_status) && mem_q != q_status)
		{
			i++;
			continue ;
		}
		else if (line[i] == '\\' && line[i + 1]
			&& (line[i + 1] == '\'' || line[i + 1] == '\"'))
			i++;
		i++;
		len++;
	}
	return (len);
}

char	*remove_quotes(char *line, size_t i, enum e_quote_status q_status)
{
	char				*new_line;
	size_t				len;
	enum e_quote_status	mem_q;

	if (!line)
		return (NULL);
	new_line = malloc((quoteless_len(line, q_status) + 1) * sizeof(*new_line));
	if (!new_line)
		return (perror_malloc("test"), free(line), NULL);
	len = 0;
	while (line[i])
	{
		mem_q = q_status;
		if (is_between_quotes(line[i], &q_status) && mem_q != q_status)
		{
			i++;
			continue ;
		}
		else if (line[i] == '\\' && line[i + 1]
			&& is_inset(line[i + 1], "\'\""))
			i++;
		new_line[len++] = line[i++];
	}
	new_line[len] = '\0';
	return (free(line), new_line);
}
