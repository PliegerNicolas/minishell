/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_first.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:52:53 by nicolas           #+#    #+#             */
/*   Updated: 2023/05/09 18:55:37 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*replace_first(char *str, const char *substr,
	const char *replacement)
{
	char	*new_str;
	char	*pos;
	size_t	lens[3];

	if (!str || !substr || !replacement)
		return (str);
	lens[0] = ft_strlen(str);
	pos = ft_strnstr(str, substr, lens[0]);
	lens[1] = ft_strlen(substr);
	lens[2] = ft_strlen(replacement);
	new_str = malloc((lens[0] + lens[2] - lens[1] + 1) * sizeof(*new_str));
	if (!new_str)
	{
		perror_malloc("@variable_name (srcs/parsing/substitute_variables.c #sub\
stitute_variables)");
		return (free(str), NULL);
	}
	ft_memcpy(new_str, str, pos - str);
	ft_memcpy(new_str + (pos - str), replacement, lens[2]);
	ft_memcpy(new_str + (pos - str) + lens[2], pos + lens[1],
		str + lens[0] - (pos + lens[1]));
	new_str[lens[0] + (lens[2] - lens[1])] = '\0';
	return (free(str), new_str);
}
