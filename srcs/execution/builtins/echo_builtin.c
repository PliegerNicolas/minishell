/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:35:59 by nplieger          #+#    #+#             */
/*   Updated: 2023/04/27 14:52:39 by nplieger         ###   ########.fr       */
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

static int	initialize_put(char *str, char ***args, t_bool *n_opt)
{
	size_t	i;

	i = 5;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str + i && ft_strncmp(str + i, "-n", 2) == 0
		&& str + i + 2 && (ft_isspace(str[i + 2]) || !str[i + 2]))
	{
		*n_opt = TRUE;
		i += 3;
	}
	while (**args && ***args == '-')
		(*args)++;
	return (i);
}

// normer
// decaller les espaces d'arg qui ont ete imprimes dans ""
// gerer les echo -nnnnnn ou echo -n -n
static t_bool	put(char *str, char **args, t_bool *n_opt, enum e_quote_status quote_status)
{
	size_t	i;

	i = initialize_put(str, &args, n_opt);
	while (str[i] && next_is_valid_word(str + i))
	{
		set_quotestatus((char *)(str + i), &quote_status);
		if (quote_status)
		{
			i++;
			while (str[i] && quote_status)
			{
				if (!set_quotestatus((char *)(str + i), &quote_status))
					ft_putchar_fd(str[i], STDOUT);
				i++;
				(*args)++;
			}
		}
		else if (str[i] == '-')
		{
			while (str[i] && !ft_isspace(str[i]))
				ft_putchar_fd(str[i++], STDOUT);
			if (next_is_valid_word(str + i))
				ft_putchar_fd(' ', STDOUT);
		}
		else if (*args && ft_strncmp(str + i, *args, ft_strlen(*args)) == 0)
		{
			ft_putstr_fd(*args, STDOUT);
			i += ft_strlen(*args);
			args++;
			if (next_is_valid_word(str + i))
				ft_putchar_fd(' ', STDOUT);
		}
		else
			i++;
	}
	return (FALSE);
}

t_bool	echo_builtin(t_lexer *lexer)
{
	t_bool	n_opt;

	if (!lexer)
		return (FALSE);
	if (ft_strarrlen((const char **)lexer->args) > 1)
	{
		n_opt = FALSE;
		if (put(lexer->cmd, lexer->args + 1, &n_opt, none))
			return (g_status = general_failure, TRUE);
		if (!n_opt)
			ft_putchar_fd('\n', STDOUT);
	}
	return (g_status = success, FALSE);
}
