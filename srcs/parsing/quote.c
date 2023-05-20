/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:17:40 by nicolas           #+#    #+#             */
/*   Updated: 2023/05/20 21:35:48 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static size_t	len_without_quotes(char *line, enum e_quote_status q_status)
{
	size_t				i;
	size_t				len;
	enum e_quote_status	mem_q;

	i = 0;
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
			&& (line[i + 1] == '\'' || line[i + 1] == '\"'))
			i++;
		i++;
		len++;
	}
	return (len);
}

/*
	A simple function that removes quotes from a given string.
*/
char	*remove_quotes(char *line, enum e_quote_status q_status)
{
	char				*new_line;
	size_t				i;
	size_t				len;
	enum e_quote_status	mem_q;

	if (!line)
		return (NULL);
	len = len_without_quotes(line, q_status);
	new_line = malloc((len + 1) * sizeof(*new_line));
	if (!new_line)
		return (perror_malloc("test"), free(line), NULL);
	i = 0;
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
