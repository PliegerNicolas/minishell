/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:17:40 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/23 14:48:39 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/*
	This function updates the quote_status variable as a pointer.
	If *quote_status has been modified (a.k.a a hidden quote has been found),
	it returns TRUE. Else FALSE.
*/
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

/*
	This function reads through a string and verifies if every
	quote is closed correctly.
	It returns TRUE if there is an error. Else FALSE.
*/
t_bool	quote_error(char *s, enum e_quote_status quote_status)
{
	int		i;

	if (!s)
		return (FALSE);
	i = 0;
	while (s[i])
		set_quotestatus(s + i++, &quote_status);
	if (quote_status != none)
		return (TRUE);
	return (FALSE);
}
