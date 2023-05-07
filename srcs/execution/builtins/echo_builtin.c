/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:35:59 by nplieger          #+#    #+#             */
/*   Updated: 2023/05/07 17:49:46 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void	skip_spaces(const char *s, const char *next_arg, size_t *i)
{
	if (next_arg)
	{
		while (s[*i] && ft_strncmp(s + *i, next_arg, ft_strlen(next_arg))
			&& ft_isspace(s[*i]))
			(*i)++;
	}
	else
		while (s[*i] && ft_isspace(s[*i]))
			(*i)++;
}

static size_t	setup(const char *s, const char *first_arg, t_bool *n_opt)
{
	size_t	i;
	size_t	j;

	i = 4;
	j = 1;
	skip_spaces(s, first_arg, &i);
	if (s[i] && s[i] == '-' && s[i + j] == 'n')
	{
		while (s[i + j] && s[i + j] == 'n')
			j++;
		if (!s[i + j] || (s[i + j] && ft_isspace(s[i + j])))
		{
			*n_opt = TRUE;
			i += j;
		}
	}
	skip_spaces(s, first_arg, &i);
	return (i);
}

static t_bool	next_is_valid_word(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && ft_isspace(s[i]))
		i++;
	if (s[i] && s[i] != '<' && s[i] != '>')
		return (TRUE);
	return (FALSE);
}

static void	echo(const char *s, const char **args, t_bool *n_opt)
{
	size_t	i;
	size_t	j;

	j = 1;
	while (args[j] && *args[j] == '-')
		j++;
	i = setup(s, args[j], n_opt);
	while (s[i] && next_is_valid_word(s + i))
	{
		if (s[i] == '-')
			while (s[i] && !ft_isspace(s[i]))
				ft_putchar_fd(s[i++], STDOUT);
		else
		{
			i += ft_strlen(args[j]);
			ft_putstr_fd((char *)args[j++], STDOUT);
		}
		if (s[i] && next_is_valid_word(s + i))
		{
			skip_spaces(s, args[j], &i);
			ft_putchar_fd(' ', STDOUT);
		}
	}
}

t_bool	echo_builtin(t_lexer *lexer)
{
	char	*quoteless_str;
	t_bool	n_opt;

	if (!lexer)
		return (FALSE);
	if (ft_strarrlen((const char **)lexer->args) <= 0)
	{
		ft_putchar_fd('\n', STDOUT);
		return (FALSE);
	}
	quoteless_str = get_quoteless_str(lexer->cmd);
	if (!quoteless_str)
		return (TRUE);
	n_opt = FALSE;
	echo(quoteless_str, (const char **)lexer->args, &n_opt);
	free(quoteless_str);
	if (!n_opt)
		ft_putchar_fd('\n', STDOUT);
	return (g_status = success, FALSE);
}

/*
static t_bool	next_is_valid_word(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] && str[i] != '<' && str[i] != '>')
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
		if (cmd[i] && next_is_valid_word(cmd + i))
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
		free(quoteless_str);
		if (!n_opt)
			ft_putchar_fd('\n', STDOUT);
	}
	else
		ft_putchar_fd('\n', STDOUT);
	return (g_status = success, FALSE);
}
*/
