/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setsplit_quotesafe.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 23:24:21 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/19 13:31:21 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/*
	This function checks if a given character in present in the given set
	while no quote is open.

	@quote_status : if != none, a quote is open.
	@c : given character to test.
	@set : given set.

	- whitelist_quote() : this function opens a specific quote (" or ') if
						  the character is given and
						  returns TRUE if a quote is open. Else return FALSE.
						  If a quote is open, it closes it.
	
	Returns TRUE if character is in set and quote is closes.
	else returns FALSE.
*/
static t_bool	is_inset(char c, const char *set,
	enum e_quote_status *quote_status)
{
	int		i;

	if (!set || !*set)
		return (FALSE);
	i = 0;
	while (set[i])
	{
		whitelist_quote(c, quote_status);
		if (c == set[i] && *quote_status == none)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

/*
	This function counts the number of sections in a string
	following a character set.
	If a quote is open, character set is ignored.

	@count : returned sections count;
	@quote_status : An enumerator that describes if a quote is
					open (none, single_quote, double_quote).

	- is_isspace() : verifies if given character is a whitespace
					 character.

	Returns 0 if empty string.
	Returns 0 if only characters contained
	in the set are present.
	Returns the number of sections separated by the set.
	The last section doesn't need to be terminated by the set.
*/
static size_t	ft_sections(const char *s, const char *set)
{
	size_t				count;
	size_t				i;
	enum e_quote_status	quote_status;

	if (!s || !*s || !set || !*set || contains_quote(set))
		return (0);
	count = 0;
	i = 0;
	quote_status = none;
	while (s[i])
	{
		while ((s[i] && is_inset(s[i], set, &quote_status)) || ft_isspace(s[i]))
			i++;
		if (!s[i])
			break ;
		while (s[i + 1] && !is_inset(s[i], set, &quote_status))
			i++;
		is_inset(s[i], set, &quote_status);
		if (s[i++])
			count++;
	}
	if (quote_status != none)
		return (perror_quote("@quote_status \
(srcs/lexical_analysis/split_by_set_quote_safe.c #ft_sections)"), 0);
	return (count);
}

/*
	This function mallocs and returns a string following the given set.

	@section : the returned string.
	@quote_status : An enumerator that describes if a quote is
					open (none, single_quote, double_quote).

	Returns NULL if only whitespaces are present until a character of
	the set is met.
	Returns the given string if no set character is met.
	Returns a substring of the given string from start to where a characeter
	of the set is met.
	
*/
static char	*get_section(const char *line, const char *set, size_t *i)
{
	char				*section;
	size_t				j;
	enum e_quote_status	quote_status;

	if (!line || !*line || !set || !*set)
		return (NULL);
	quote_status = none;
	while (is_inset(line[*i], set, &quote_status))
		(*i)++;
	j = 0;
	while (line[*i + j] && !is_inset(line[*i + j], set, &quote_status))
		j++;
	section = malloc((j + 1) * sizeof(*section));
	if (!section)
		return (NULL);
	j = 0;
	while (line[*i] && !is_inset(line[*i], set, &quote_status))
		section[j++] = line[(*i)++];
	section[j] = '\0';
	return (section);
}

/*
	This function free the splitted_commands (char **).
*/
static void	free_split(char **splitted_commands)
{
	int		i;

	if (splitted_commands)
	{
		i = 0;
		while (splitted_commands[i])
			free(splitted_commands[i++]);
		free(splitted_commands);
	}
}

/*
	This function splitteds a given sting following a set.
	This set is ignored if a quote has been opened.

	@splitted_commands : returns value.
	@sections : number of considered sections in the given string.
	@line_index : The read index of the given string.

	- ft_sections() : counts sections.
	- get_section() : retrieves a section and increments
					  line_index accordingly.
	- free_split() : frees the splitted_commands variable.

	Returns empty char** if string only contains characters of
	the set or whitespace characters.
	Returns NULL on malloc error.
	Return splitted string otherwise, ended by NULL.
*/
char	**ft_setsplit_quotesafe(const char *line, const char *set)
{
	char	**splitted_commands;
	size_t	sections;
	size_t	i;
	size_t	line_index;

	if (!line || !*line || contains_quote(set))
		return (NULL);
	sections = ft_sections(line, set);
	splitted_commands = malloc((sections + 1) * sizeof(*splitted_commands));
	if (!splitted_commands)
		return (NULL);
	i = 0;
	line_index = 0;
	while (i < sections)
	{
		splitted_commands[i] = get_section(line, set, &line_index);
		if (!splitted_commands[i])
			return (free_split(splitted_commands), NULL);
		i++;
	}
	splitted_commands[i] = '\0';
	return (splitted_commands);
}
