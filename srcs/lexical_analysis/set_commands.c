/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 22:59:15 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/14 01:45:22 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_commands	*set_commands(const char *line)
{
	char		**test;
	t_commands	*commands;

	if (!line)
		return (NULL);
	test = ft_split_by_set_quote_safe(line, ";");
	(void)test;
	commands = NULL;
	return (commands);
}
