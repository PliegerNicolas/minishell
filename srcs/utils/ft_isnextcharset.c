/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnextcharset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:21:52 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/24 13:53:42 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_isnextcharset(const char *s, const char *set)
{
	if (!s || !set)
		return (0);
	while (ft_isspace(*s))
		s++;
	while (*s && *set && *s == *set)
	{
		s++;
		set++;
	}
	if (!*set)
		return (1);
	return (0);
}
