/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setsplit_quotesafe.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 23:24:21 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/25 20:57:22 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static t_bool	is_inset(char c, const char *set)
{
	int		i;

	if (!set || !*set)
		return (FALSE);
	i = 0;
	while (set[i])
		if (c == set[i++])
			return (TRUE);
	return (FALSE);
}

static size_t	ft_sections(const char *s, const char *set,
	enum e_quote_status quote_status)
{
	size_t				count;
	size_t				i;

	if (!s || !*s || !set || !*set)
		return (0);
	count = 0;
	i = 0;
	while (s[i])
	{
		while ((s[i] && is_inset(s[i], set)) || ft_isspace(s[i])
			|| set_quotestatus((char *)(s + i), &quote_status))
			i++;
		if (!s[i])
			break ;
		while (s[i + 1] && (!is_inset(s[i], set) || quote_status))
			set_quotestatus((char *)(s + i++), &quote_status);
		is_inset(s[i], set);
		if (s[i++])
			count++;
	}
	return (count);
}

static char	*get_section(const char *line, const char *set, size_t *i,
	enum e_quote_status *quote_status)
{
	char				*section;
	size_t				j;

	if (!line || !*line || !set || !*set)
		return (NULL);
	while (line[*i] && is_inset(line[*i], set))
		(*i)++;
	j = 0;
	while (line[*i + j] && (!is_inset(line[*i + j], set) || *quote_status))
		set_quotestatus((char *)(line + *i + j++), quote_status);
	section = malloc((j + 1) * sizeof(*section));
	if (!section)
		return (NULL);
	j = 0;
	while (line[*i] && (!is_inset(line[*i], set) || *quote_status))
	{
		set_quotestatus((char *)(line + *i), quote_status);
		section[j++] = line[(*i)++];
	}
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
