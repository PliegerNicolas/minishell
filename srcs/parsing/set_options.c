/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:48:09 by nicolas           #+#    #+#             */
/*   Updated: 2023/04/02 04:03:09 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/*
	This function generates a quoteless_str safely without destroying
	the given const string.
*/
static char	*get_quoteless_str(const char *str)
{
	char	*quoteless_str;

	if (!str)
		return (NULL);
	quoteless_str = ft_strdup(str);
	if (!quoteless_str)
		return (perror_malloc("@quoteless_str (srcs/parsing/set_options.c #get_\
quoteless_str)"), NULL);
	quoteless_str = remove_quotes(quoteless_str, none);
	if (!quoteless_str)
		return (NULL);
	return (quoteless_str);
}

/*
	This function reads through the given quoteless_str. It then counts
	how many chars can be considered as a valid option.
	If format is not valid, returns 0.
	Else returns the given len.
*/
static size_t	get_option_len(char *quoteless_str)
{
	size_t	len;

	if (!quoteless_str)
		return (0);
	len = 0;
	if (*quoteless_str != '-' || !*(quoteless_str + 1))
		return (0);
	while (ft_isnextcharset(quoteless_str + len, "-"))
	{	
		while (*(quoteless_str + len) && ft_isspace(*(quoteless_str + len)))
			quoteless_str++;
		quoteless_str++;
		while (*(quoteless_str + len) && ft_isalpha(*(quoteless_str + len)))
			len++;
	}
	if (*(quoteless_str + len))
		return (0);
	return (len);
}

/*
	This function generates the string containing every char that describes
	an option by parsing the quoteless_str.

	Returns NULL on error.  Else returns the additional_options string.
*/
static char	*get_option_chars(char *quoteless_str, size_t len)
{
	char	*additional_options;
	size_t	i;

	if (!quoteless_str)
		return (NULL);
	if (!len)
		return (perror_invalid_options(), NULL);
	additional_options = malloc((len + 1) * sizeof(*additional_options));
	if (!additional_options)
		return (perror_malloc("@additional_options (srcs/parsing/set_options.c \
#get_option_chars)"), NULL);
	len = 0;
	i = 0;
	if (*quoteless_str != '-' || !*(quoteless_str + 1))
		return (NULL);
	while (ft_isnextcharset(quoteless_str + len, "-"))
	{	
		while (*(quoteless_str + len) && ft_isspace(*(quoteless_str + len)))
			quoteless_str++;
		quoteless_str++;
		while (*(quoteless_str + len) && ft_isalpha(*(quoteless_str + len)))
			additional_options[i++] = *(quoteless_str + len++);
	}
	additional_options[i] = '\0';
	return (additional_options);
}

/*
	This function appends the additional_options string to the lexer->options
	field.
	Returns TRUE on error. Else FALSE on success.
*/
static t_bool	join_options(t_lexer *lexer, char *additional_options)
{
	char	*joined_options;

	if (!additional_options)
		return (FALSE);
	if (!lexer->options)
		lexer->options = additional_options;
	else
	{
		joined_options = ft_strjoin(lexer->options, additional_options);
		free(additional_options);
		if (!joined_options)
			return (perror_malloc("@joined_options (srcs/parsing/set_options.c \
#joined_options)"), TRUE);
		free(lexer->options);
		lexer->options = joined_options;
	}
	return (FALSE);
}

/*
	This function appends found option characters (preceding a '-' char) to
	the existing options string contained in the lexer.
	If lexer's options field is empty, fill it.
	If there is an error, it preserves the string but returns TRUE to tell the
	lexer should be freed and the program exited.

	@quoteless_str : the given str with quotes removed.
	@additional_options : the new options string that should be joined to the
						  already existing one.

	- get_quoteless_str() : it removes the quotes from the given str safely.
	- get_option_len() : counts the number of chars considered as an option.
	- get_option_chars() : mallocs and returns the string containing the chars
						   representing the options.
	- join _options() : joins the options string to the already existing one
					    if he exists.

	returns FALSE if everything goes alright. Returns TRUE if an error occured.
*/
t_bool	set_options(const char *str, t_lexer *lexer)
{
	char	*quoteless_str;
	char	*additional_options;

	if (!str)
		return (FALSE);
	quoteless_str = get_quoteless_str(str);
	if (!quoteless_str)
		return (TRUE);
	additional_options = get_option_chars(quoteless_str,
			get_option_len(quoteless_str));
	free(quoteless_str);
	if (!additional_options)
		return (TRUE);
	if (join_options(lexer, additional_options))
		return (TRUE);
	return (FALSE);
}
