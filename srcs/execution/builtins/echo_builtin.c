/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 18:46:41 by nicolas           #+#    #+#             */
/*   Updated: 2023/04/06 15:54:16 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static char	*get_quoteless_str(const char *str)
{
	char	*quoteless_str;

	if (!str)
		return (NULL);
	quoteless_str = ft_strdup(str);
	if (!quoteless_str)
		return (perror_malloc("@quoteless_str (srcs/execution/builtins/echo_bui\
ltin.c #get_quoteless_str)"), NULL);
	quoteless_str = remove_quotes(quoteless_str, none);
	if (!quoteless_str)
		return (NULL);
	return (quoteless_str);
}

static void	skip_command(const char *quoteless_line, size_t *i)
{
	while (quoteless_line[*i])
	{
		while (quoteless_line[*i] && ft_isspace(quoteless_line[*i]))
			(*i)++;
		if (quoteless_line[*i] != '-')
			break ;
		while (!ft_isspace(quoteless_line[*i]))
			(*i)++;
	}
}

t_bool	echo_builtin(t_lexer *lexer, char ***envp)
{
	char	*quoteless_line;
	size_t	i;

	if (!envp || !lexer->cmd)
		return (g_status = command_invoked_cannot_execute, TRUE);
	quoteless_line = get_quoteless_str(lexer->cmd);
	if (!quoteless_line)
		return (g_status = general_failure, TRUE);
	i = 4;
	skip_command(quoteless_line, &i);
	if (lexer->options && ft_strncmp(lexer->options, "n", 2) == 0)
	{
		ft_putstr_fd(quoteless_line + i, STDOUT);
		ft_putendl_fd("$", STDOUT);
	}
	else
		ft_putendl_fd(quoteless_line + i, STDOUT);
	return (free(quoteless_line), FALSE);
}
