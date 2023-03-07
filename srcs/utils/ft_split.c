/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:58:11 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/06 10:58:24 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static size_t	ft_count_sections(char const *s, char const c)
{
	size_t		sections;
	size_t		i;

	if (!*s)
		return (0);
	i = 0;
	sections = 0;
	while (s && s[i])
	{
		if (s[i] != c)
		{
			sections++;
			while (s[i] != c && s[i])
				i++;
		}
		if (s[i])
			i++;
	}
	return (sections);
}

static size_t	ft_section_len(char const *s, char const c, size_t i)
{
	size_t		len;

	len = 0;
	while (s[i] && s[i] != c)
	{
		len++;
		i++;
	}
	return (len);
}

static int	ft_free_2d_tab(char **tab, size_t i)
{
	if (!tab[i])
	{
		while (i-- > 0)
			free(tab[i]);
		free(tab);
		return (0);
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char		**ret;
	size_t		i;
	size_t		j;
	size_t		sections;
	size_t		section_len;

	i = 0;
	j = 0;
	sections = ft_count_sections(s, c);
	ret = malloc((sections + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	while (j < sections)
	{
		while (s[i] == c)
			i++;
		section_len = ft_section_len(s, c, i);
		ret[j] = ft_substr(s, i, section_len);
		if (!ft_free_2d_tab(ret, j))
			return (NULL);
		i += section_len;
		j++;
	}
	ret[j] = 0;
	return (ret);
}
