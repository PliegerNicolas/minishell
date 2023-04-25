/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laliao <laliao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 18:46:41 by nicolas           #+#    #+#             */
/*   Updated: 2023/04/25 21:49:47 by laliao           ###   ########.fr       */
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

char	**get_array_echo(t_lexer *lexer, char **split, char **new_args)
{
	char	*tmp_split;
	size_t	i;
	size_t	j;
	size_t	new;

	j = 0;
	i = 0;
	new = 0;
	while (split[i])
	{
		tmp_split = get_quoteless_str(split[i]);
		if (!lexer->args[j])
		{
			i++;
			j = 0;
		}
		else if (split[i][0] == '-' && ft_strlen(split[i]) > 2)
		{
			new_args[new++] = ft_strdup(split[i]);
			i++;
		}
		else if (strcmp(tmp_split, lexer->args[j]) == 0)
		{
			new_args[new++] = ft_strdup(lexer->args[j]);
			i++;
			j = 0;
		}
		free(tmp_split);
		j++;
	}
	return (new_args);
}

char	**reparse_echo(t_lexer *lexer)
{
	char	**new_args;
	char	**split;
	size_t	i;

	i = 0;
	split = ft_setsplit_quotesafe(lexer->cmd, WHITE_SPACES, none);
	if (!split)
		return (free_lexer(lexer), NULL);
	while (lexer->args[i])
		i++;
	new_args = calloc(i + 1, sizeof(char *));
	new_args = get_array_echo(lexer, split, new_args);
	free_str_arr(split);
	free_str_arr(lexer->args);
	return (new_args);
}

static t_bool	put(t_lexer *lexer, t_bool n_option, size_t i)
{
	char	*quoteless_str;

	while (lexer->args[i])
	{
		quoteless_str = ft_strdup(lexer->args[i++]);
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
	t_bool	n_option;
	size_t	i;

	if (!lexer)
		return (FALSE);
	n_option = FALSE;
	i = 1;
	lexer->args = reparse_echo(lexer);
	if (!lexer->args)
		return (FALSE);
	if (lexer->args[i] && strncmp(lexer->args[i], "-n", 2) == 0)
	{
		n_option = TRUE;
		i++;
	}
	if (put(lexer, n_option, i))
		return (g_status = general_failure, TRUE);
	return (g_status = success, FALSE);
}
