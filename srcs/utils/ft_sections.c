/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:12:21 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/12 19:33:28 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

size_t	ft_sections(const char *s, const char *set)
{
	size_t	count;
	int		i;
	int		j;

	if (!s || !*s || !set || !*set)
		return (0);
	count = 1;
	i = 0;
	while (s[i])
	{
		j = 0;
		while (s[i + j] == set[j])
		{
			if (set[j + 1] == '\0')
			{
				i += j;
				if (s[i + 1])
					count++;
				break ;
			}
			j++;
		}
		i++;
	}
	return (count);
}
