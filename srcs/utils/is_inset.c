/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_inset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:44:03 by nicolas           #+#    #+#             */
/*   Updated: 2023/05/20 17:44:15 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_bool	is_inset(char c, const char *set)
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
