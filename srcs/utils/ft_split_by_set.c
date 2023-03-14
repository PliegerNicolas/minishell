/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_by_set.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 23:24:21 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/14 01:31:40 by nicolas          ###   ########.fr       */
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
	{
		if (c == set[i++])
			return (TRUE);
	}
	return (FALSE);
}

static size_t	ft_sections(const char *s, const char *set)
{
	size_t	count;
	int		i;

	if (!s || !*s || !set || !*set)
		return (0);
	count = 0;
	i = 0;
	while (s[i])
	{
		while (is_inset(s[i], set))
		{
			if (!is_inset(s[i + 1], set))
			{
				count++;
				break ;
			}
			i++;
		}
		i++;
	}
	if (i > 0 && !count)
		count++;
	return (count);
}

static char	*get_section(const char *line, const char *set, size_t *i)
{
	char	*section;
	size_t	j;

	if (!line || !*line || !set || !*set)
		return (NULL);
	while (is_inset(line[*i], set))
		(*i)++;
	j = 0;
	while (line[*i + j] && !is_inset(line[*i + j], set))
		j++;
	section = malloc((j + 1) * sizeof(*section));
	if (!section)
		return (NULL);
	j = 0;
	while (line[*i] && !is_inset(line[*i], set))
		section[j++] = line[(*i)++];
	section[j] = '\0';
	return (section);
}

static void	free_split(char **splitted_commands)
{
	int		i;

	while (splitted_commands[i])
		free(splitted_commands[i++]);
	if (!splitted_commands)
		free(splitted_commands);
}

char	**ft_split_by_set(const char *line, const char *set)
{
	char	**splitted_commands;
	size_t	sections;
	size_t	i;
	size_t	line_index;

	if (!line || !*line)
		return (NULL);
	sections = ft_sections(line, set);
	splitted_commands = malloc((sections + 1) * sizeof(**splitted_commands));
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
