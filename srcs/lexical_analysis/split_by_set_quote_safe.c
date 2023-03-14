/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_set_quote_safe.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 23:24:21 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/14 14:54:27 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

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
		return (perror_quote("@quote_status (srcs/lexical_analysis/split_by_set_quote_safe.c #ft_sections)"), 0);
	return (count);
}

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

char	**ft_split_by_set_quote_safe(const char *line, const char *set)
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
