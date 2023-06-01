/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_only_whitespace.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:48:09 by nicolas           #+#    #+#             */
/*   Updated: 2023/06/01 13:40:52 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_bool	ft_only_whitespace(const char *str)
{
	char	*quoteless_str;

	quoteless_str = get_quoteless_str(str);
	if (!quoteless_str)
		return (perror_malloc("test"), TRUE);
	while (*quoteless_str)
	{
		if (!ft_isspace(*quoteless_str))
			return (FALSE);
		quoteless_str++;
	}
	return (TRUE);
}
