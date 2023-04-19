/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 18:46:41 by nicolas           #+#    #+#             */
/*   Updated: 2023/04/19 16:17:00 by nicolas          ###   ########.fr       */
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

static t_bool	put(t_lexer *lexer, t_bool n_option, size_t i)
{
	char	*quoteless_str;

	while (lexer->args[i])
	{
		quoteless_str = get_quoteless_str(lexer->args[i++]);
		if (!quoteless_str)
			return (TRUE);
		ft_putstr_fd(quoteless_str, STDOUT);
		free(quoteless_str);
		if (lexer->args[i])
			ft_putchar_fd(' ', STDOUT);
	}
	if (!n_option)
		ft_putchar_fd('\n', STDOUT);
	else if (n_option && i > 2)
		ft_putendl_fd("$", STDOUT);
	return (FALSE);
}

/* Problème avec l'impression des options dû à la stratégie de parsing. */
t_bool	echo_builtin(t_lexer *lexer)
{
	char	*quoteless_str;
	t_bool	n_option;
	size_t	i;

	if (!lexer)
		return (FALSE);
	quoteless_str = get_quoteless_str(lexer->cmd);
	if (!quoteless_str)
		return (g_status = general_failure, TRUE);
	n_option = FALSE;
	i = 1;
	if (lexer->args[i] && strncmp(lexer->args[i], "-n", 2) == 0)
	{
		n_option = TRUE;
		i++;
	}
	if (put(lexer, n_option, i))
		return (g_status = general_failure, TRUE);
	return (g_status = success, FALSE);
}
