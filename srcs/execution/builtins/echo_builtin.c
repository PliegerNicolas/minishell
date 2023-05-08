/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:35:59 by nplieger          #+#    #+#             */
/*   Updated: 2023/05/08 13:09:08 by nicolas          ###   ########.fr       */
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
	size_t	i;

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
	i = 0;
	while (quoteless_str[i] && ft_isspace(quoteless_str[i]))
		i++;
	n_opt = FALSE;
	echo(quoteless_str + i, (const char **)lexer->args, &n_opt);
	free(quoteless_str);
	if (!n_opt)
		ft_putchar_fd('\n', STDOUT);
	return (g_status = success, FALSE);
}
