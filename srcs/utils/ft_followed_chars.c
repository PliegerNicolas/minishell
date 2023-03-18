/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_followed_chars.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 18:19:19 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/18 03:22:47 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_followed_chars(const char *s, const int c1, const int c2)
{
	int	c1_found;

	if (!s || !c1 || !c2)
		return (0);
	c1_found = 0;
	while (*s && !ft_isspace(*s))
	{
		if (!c1_found && *s == (unsigned char)c2)
			return (0);
		else if (!c1_found && *s == (unsigned char)c1)
			c1_found = 1;
		else if (c1_found && *s == (unsigned char)c1)
			return (0);
		else if (c1_found && *s == (unsigned char)c2)
			return (1);
		s++;
	}
	if (c1_found)
		return (0);
	return (1);
}
