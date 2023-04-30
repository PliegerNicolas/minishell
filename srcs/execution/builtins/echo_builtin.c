/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:35:59 by nplieger          #+#    #+#             */
/*   Updated: 2023/04/30 09:25:59 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static t_bool	next_is_valid_word(char *str)
{
	while (*str && ft_isspace(*str))
		str++;
	if (*str && *str != '<' && *str != '>')
		return (TRUE);
	return (FALSE);
}

static size_t	set_cursor_and_n_opt(char *cmd, t_bool *n_opt)
{
	size_t	i;
	size_t	j;

	i = 4;
	while (cmd[i] && ft_isspace(cmd[i]))
		i++;
	j = 1;
	if (cmd[i] && cmd[i] == '-' && cmd[i + j] == 'n')
	{
		while (cmd[i + j] && cmd[i + j] == 'n')
			j++;
		if (!cmd[i + j] || (cmd[i + j] && ft_isspace(cmd[i + j])))
		{
			*n_opt = TRUE;
			i += j;
		}
	}
	while (cmd[i] && ft_isspace(cmd[i]))
		i++;
	return (i);
}

static void	put(char *cmd, char **args, t_bool *n_opt)
{
	size_t				i;
	size_t				j;

	i = set_cursor_and_n_opt(cmd, n_opt);
	j = 1;
	while (args[j] && *args[j] == '-')
		j++;
	while (cmd[i] && next_is_valid_word(cmd + i))
	{
		if (cmd[i] == '-')
			while (cmd[i] && !ft_isspace(cmd[i]))
				ft_putchar_fd(cmd[i++], STDOUT);
		else
		{
			ft_putstr_fd(args[j], STDOUT);
			i += ft_strlen(args[j]);
			j++;
		}
		if (next_is_valid_word(cmd + i))
		{
			while (cmd[i] && ft_isspace(cmd[i]))
				i++;
			ft_putchar_fd(' ', STDOUT);
		}
	}
}

static char	*get_quoteless_str(const char *str)
{
	char	*quoteless_str;

	if (!str)
		return (NULL);
	quoteless_str = ft_strdup(str);
	if (!quoteless_str)
		return (perror_malloc("@quoteless_str (srcs/parsing/set_options.c #get_\
quoteless_str)"), NULL);
	quoteless_str = remove_quotes(quoteless_str, none);
	if (!quoteless_str)
		return (NULL);
	return (quoteless_str);
}

t_bool	echo_builtin(t_lexer *lexer)
{
	char	*quoteless_str;
	t_bool	n_opt;

	if (!lexer)
		return (FALSE);
	if (ft_strarrlen((const char **)lexer->args) > 1)
	{
		n_opt = FALSE;
		quoteless_str = get_quoteless_str(lexer->cmd);
		if (!quoteless_str)
			return (g_status = general_failure, TRUE);
		put(quoteless_str, lexer->args, &n_opt);
		if (!n_opt)
			ft_putchar_fd('\n', STDOUT);
	}
	else
		ft_putchar_fd('\n', STDOUT);
	return (g_status = success, FALSE);
}
