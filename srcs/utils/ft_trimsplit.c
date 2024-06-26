/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trimsplit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 00:30:34 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/14 14:37:41 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

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

char	**ft_trimsplit(const char **split, const char *set)
{
	char	**trimmed_split;
	int		i;

	if (!split)
		return (NULL);
	i = 0;
	while (split[i])
		i++;
	trimmed_split = malloc((i + 1) * sizeof(*trimmed_split));
	if (!trimmed_split)
		return (NULL);
	i = 0;
	while (split[i])
	{
		trimmed_split[i] = ft_strtrim(split[i], set);
		if (!trimmed_split[i])
			return (free_split(trimmed_split), NULL);
		i++;
	}
	trimmed_split[i] = '\0';
	free_split((char **)split);
	return (trimmed_split);
}
