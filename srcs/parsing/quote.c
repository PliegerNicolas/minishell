/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:17:40 by nicolas           #+#    #+#             */
/*   Updated: 2023/05/20 20:33:14 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/*
	This function updates the quote_status variable as a pointer.
	If *quote_status has been modified (a.k.a a hidden quote has been found),
	it returns TRUE. Else FALSE.
*/
/*
t_bool	set_quotestatus(char *s, enum e_quote_status *quote_status)
{
	enum e_quote_status	mem_quote;
	static t_bool		found_backslash;

	if (!found_backslash && *(s + 1) && *s == '\\')
		return (found_backslash = TRUE, TRUE);
	else if (found_backslash && *s)
		return (found_backslash = FALSE, FALSE);
	mem_quote = *quote_status;
	if (*quote_status == none)
	{
		if (*s == '\'')
			*quote_status = single_quote;
		else if (*s == '\"')
			*quote_status = double_quote;
	}
	else if (*quote_status == single_quote && *s == '\'')
		*quote_status = none;
	else if (*quote_status == double_quote && *s == '\"')
		*quote_status = none;
	if (mem_quote == *quote_status)
		return (FALSE);
	return (TRUE);
}
*/

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
		else if (line[i] == '\\' && line[i + 1] && (line[i + 1] == '\'' || line[i + 1] == '\"'))
			i++;
		i++;
		len++;
	}
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
		else if (line[i] == '\\' && line[i + 1] && (line[i + 1] == '\'' || line[i + 1] == '\"'))
			i++;
		new_line[len++] = line[i++];
	}
	new_line[len] = '\0';
	return (free(line), new_line);
}
