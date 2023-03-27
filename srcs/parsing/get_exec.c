/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 19:46:13 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/28 00:15:23 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*get_exec(const char *str)
{
	char	*exec;

	if (!str)
		return (NULL);
	if (*str == '-')
		return (perror_command_not_found(), NULL);
	exec = ft_strdup(str);
	if (!exec)
		return (perror_malloc("@exec (srcs/parsing/get_exec.c #get_exec)"),
			NULL);
	exec = remove_quotes(exec, none);
	if (!exec)
		return (NULL);
	return (exec);
}

/*
char	*get_exec(const char *cmd, size_t *i,
	enum e_quote_status *quote_status)
{
	char	*substr;
	size_t	start;

	if (!cmd)
		return (NULL);
	while (cmd[*i] && ft_isspace(cmd[*i]))
		(*i)++;
	if (cmd[*i] == '-')
		return (perror_command_not_found(), NULL);
	start = *i;
	while (cmd[*i] && (!ft_isspace(cmd[*i]) || *quote_status))
		set_quotestatus((char *)(cmd + (*i)++), quote_status);
	substr = ft_substr(cmd, start, *i);
	if (!substr)
		return (perror_malloc("@substr (srcs/parsing/get_exec.c #get_exec)"),
			NULL);
	substr = remove_quotes(substr, none);
	if (!substr)
		return (perror_malloc("@substr (srcs/parsing/get_exec.c #get_exec)"),
			NULL);
	return (substr);
}
*/
