/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 23:06:08 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/14 01:33:53 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/*
	A simple function that checks if a quote is open.

	Returns TRUE or FALSE.
	If TRUE, quote is open.
	If FALSE, quote is closed.
*/
t_bool	is_open_quote(enum e_quote_status quote_status)
{
	if (quote_status != none)
		return (TRUE);
	return (FALSE);
}

/*
	This function whitelist's a quote opening and closing status.

	@c : read character. This function is ideally used in a while
		 loop on a string.
		@quote_status : pointer to quote enum holding the status.
						If status == none, then no quote has been opened.
*/
t_bool	whitelist_quote(char c, enum e_quote_status *quote_status)
{
	if (*quote_status == none)
	{
		if (c == '\'')
			*quote_status = single_quote;
		else if (c == '\"')
			*quote_status = double_quote;
	}
	else
	{
		if (c == '\'' && *quote_status == single_quote)
			*quote_status = none;
		else if (c == '\"' && *quote_status == double_quote)
			*quote_status = none;
	}
	return (is_open_quote(*quote_status));
}

/*
	A simple function that checks if a string contains
	at least on quote.

	Returns TRUE or FALSE.
	If TRUE, there is a single or double quote.
	If FALSE, there are no quotes.
*/
t_bool	contains_quote(const char *s)
{
	enum e_quote_status	quote_status;
	int					i;

	i = 0;
	quote_status = none;
	while (s[i])
	{
		if (whitelist_quote(s[i++], &quote_status))
			return (TRUE);
	}
	return (FALSE);
}
