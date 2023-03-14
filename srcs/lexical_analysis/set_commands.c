/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 22:59:15 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/14 14:42:37 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_commands	*set_commands(const char *line)
{
	char		**splitted_commands;
	t_commands	*commands;

	if (!line)
		return (NULL);
	splitted_commands = ft_split_by_set_quote_safe(line, ";");
	splitted_commands = ft_trimsplit((const char **)splitted_commands, WHITE_SPACES);
	commands = NULL;
	return (free_str_arr(splitted_commands), commands);
}
