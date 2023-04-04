/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 18:46:41 by nicolas           #+#    #+#             */
/*   Updated: 2023/04/04 18:56:39 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_bool	echo_builtin(t_lexer *lexer, char **envp)
{
	char	*line;
	size_t	i;

	if (!envp)
		return (g_status = command_invoked_cannot_execute, TRUE);
	if (lexer->options)
		return (g_status = misuse_of_shell_builtins, TRUE);
	line = ft_strdup(lexer->cmd);
	if (!line)
		return (perror_malloc("@line (srcs/execution/builtins/echo_builtin.c #e\
cho_builtin)"), g_status = general_failure, TRUE);
	line = remove_quotes(line, none);
	if (!line)
		return (g_status = general_failure, TRUE);
	i = 4;
	while (line[i] && ft_isspace(line[i]))
		i++;
	ft_putendl_fd(line + i, STDOUT);
	return (free(line), FALSE);
}
