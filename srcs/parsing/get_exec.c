/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 19:46:13 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/28 02:27:57 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/*
	This function check's if the given string starts with a '-'. If that's
	the cases, an error is printed and NULL returned.
	Else it removes potential quotes and returns the new malloced string.
*/
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
