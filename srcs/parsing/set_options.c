/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:48:09 by nicolas           #+#    #+#             */
/*   Updated: 2023/04/10 00:57:44 by nicolas          ###   ########.fr       */
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
		return (perror_malloc("@quoteless_str (srcs/parsing/set_options.c #get_\
quoteless_str)"), NULL);
	quoteless_str = remove_quotes(quoteless_str, none);
	if (!quoteless_str)
		return (NULL);
	return (quoteless_str);
}

static char	*generate_new_option(char c)
{
	char	*option_str;

	if (!c)
		return (NULL);
	option_str = malloc(3 * sizeof(*option_str));
	if (!option_str)
		return (perror_malloc("@option_str (srcs/parsing/set_options.c #generat\
e_new_option)"), NULL);
	option_str[0] = '-';
	option_str[1] = c;
	option_str[2] = '\0';
	return (option_str);
}

static t_bool	add_option(const char c, char ***options)
{
	char	*new_option_str;
	size_t	i;

	if (!c)
		return (FALSE);
	new_option_str = generate_new_option(c);
	if (!new_option_str)
		return (TRUE);
	i = 0;
	while ((*options)[i] && ft_strncmp(new_option_str, (*options)[i], 4) != 0)
		i++;
	if ((*options)[i])
		return (free(new_option_str), FALSE);
	*options = ft_append_to_string_array(*options, new_option_str);
	if (!*options)
		return (TRUE);
	return (FALSE);
}

static t_bool	append_options(const char *str, char ***options)
{
	if (!str)
		return (FALSE);
	if (*str != '-' || !*(str + 1))
		return (perror_invalid_options(), TRUE);
	while (ft_isnextcharset(str, "-"))
	{
		while (*str && ft_isspace(*str))
			str++;
		str++;
		if (!*str || !ft_isalpha(*str))
			return (perror_invalid_options(), TRUE);
		while (*str && ft_isalpha(*str))
			if (add_option(*str++, options))
				return (TRUE);
	}
	if (*str)
		return (perror_invalid_options(), TRUE);
	return (FALSE);
}

t_bool	set_options(const char *str, t_lexer *lexer)
{
	char	*quoteless_str;

	if (!str)
		return (FALSE);
	quoteless_str = get_quoteless_str(str);
	if (!quoteless_str)
		return (TRUE);
	if (!lexer->options)
	{
		lexer->options = ft_calloc(1, sizeof(*lexer->options));
		if (!lexer->options)
			return (perror_malloc("@lexer->options (srcs/parsing/set_options.c \
#set_options)"), TRUE);
	}
	if (append_options(quoteless_str, &lexer->options))
		return (free(quoteless_str), TRUE);
	free(quoteless_str);
	return (FALSE);
}
