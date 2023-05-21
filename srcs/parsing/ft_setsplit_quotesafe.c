/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setsplit_quotesafe.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 23:24:21 by nicolas           #+#    #+#             */
/*   Updated: 2023/05/20 21:17:28 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static size_t	ft_sections(const char *s, const char *set,
	enum e_quote_status quote_status)
{
	char				*tr_s;
	size_t				count;
	size_t				i;

	if (!s || !*s || !set || !*set)
		return (0);
	tr_s = ft_strtrim(s, WHITE_SPACES);
	if (!tr_s)
		return (0);
	i = 0;
	count = 1;
	while (tr_s[i])
	{
		if (!is_between_quotes(tr_s[i], &quote_status))
			if (tr_s[i] && is_inset(tr_s[i], set)
				&& !ft_only_whitespace(tr_s + i + 1))
				count++;
		i++;
	}
	return (free(tr_s), count);
}

static char	*get_section(const char *line, const char *set, size_t *i,
	enum e_quote_status *q_status)
{
	char				*section;
	enum e_quote_status	mem_q;
	size_t				j;

	if (!line || !*line || !set || !*set)
		return (NULL);
	mem_q = *q_status;
	while (line[*i] && is_inset(line[*i], set))
		(*i)++;
	j = 0;
	while (line[*i + j] && (is_between_quotes(line[*i + j], &mem_q)
			|| !is_inset(line[*i + j], set)))
		j++;
	section = malloc((j + 1) * sizeof(*section));
	if (!section)
		return (NULL);
	j = 0;
	while (line[*i] && (is_between_quotes(line[*i], q_status)
			|| !is_inset(line[*i], set)))
		section[j++] = line[(*i)++];
	section[j] = '\0';
	return (section);
}

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
	This function splits a str (line) following all the characters
	contained in the given set.
	It doesn't split the given characters contained in the set if
	between single or double quotes.

	Returns a char ** containing every string from the expected split
	or NULL on error.
*/
char	**ft_setsplit_quotesafe(const char *line, const char *set,
	enum e_quote_status quote_status)
{
	char	**splitted_commands;
	size_t	sections;
	size_t	i;
	size_t	line_index;

	if (!line || !*line)
		return (NULL);
	sections = ft_sections(line, set, none);
	splitted_commands = malloc((sections + 1) * sizeof(*splitted_commands));
	if (!splitted_commands)
		return (NULL);
	i = 0;
	line_index = 0;
	while (i < sections)
	{
		splitted_commands[i] = get_section(line, set, &line_index,
				&quote_status);
		if (!splitted_commands[i++])
			return (free_split(splitted_commands), NULL);
	}
	splitted_commands[i] = '\0';
	return (splitted_commands);
}
