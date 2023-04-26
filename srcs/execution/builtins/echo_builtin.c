/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:35:59 by nplieger          #+#    #+#             */
/*   Updated: 2023/04/26 17:37:20 by nplieger         ###   ########.fr       */
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
		&& str + i + 2 && ft_isspace(str[i + 2]))
	{
		*n_opt = TRUE;
		i += 3;
	}
	while (**args && ***args == '-')
		(*args)++;
	return (i);
}

static t_bool	put(char *str, char **args, t_bool *n_opt)
{
	size_t	i;

	i = initialize_put(str, &args, n_opt);
	while (str[i] && next_is_valid_word(str + i))
	{
		if (str[i] == '-')
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
	char	*quoteless_str;
	t_bool	n_opt;

	if (!lexer)
		return (FALSE);
	if (ft_strarrlen((const char **)lexer->args) > 1)
	{
		quoteless_str = get_quoteless_str(lexer->cmd);
		if (!quoteless_str)
			return (g_status = general_failure, TRUE);
		n_opt = FALSE;
		if (put(quoteless_str, lexer->args + 1, &n_opt))
			return (g_status = general_failure, free(quoteless_str), TRUE);
		free(quoteless_str);
		if (!n_opt)
			ft_putchar_fd('\n', STDOUT);
	}
	return (g_status = success, FALSE);
}
