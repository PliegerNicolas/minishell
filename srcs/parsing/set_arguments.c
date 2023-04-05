/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_arguments.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:47:14 by nicolas           #+#    #+#             */
/*   Updated: 2023/04/05 13:57:39 by nicolas          ###   ########.fr       */
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
		return (perror_malloc("@quoteless_str (srcs/parsing/set_arguments.c #ge\
t_quoteless_str)"), NULL);
	quoteless_str = remove_quotes(quoteless_str, none);
	if (!quoteless_str)
		return (NULL);
	return (quoteless_str);
}

static t_bool	initialize_arguments(char *quoteless_str, t_lexer *lexer)
{
	if (!quoteless_str || (lexer && lexer->args))
		return (FALSE);
	lexer->args = malloc(2 * sizeof(*lexer->args));
	if (!lexer->args)
		return (perror_malloc("@lexer->args (srcs/parsing/set_arguments.c #init\
ialize_arguments)"), TRUE);
	lexer->args[0] = quoteless_str;
	lexer->args[1] = NULL;
	return (FALSE);
}

t_bool	set_arguments(const char *str, t_lexer *lexer)
{
	char	*quoteless_str;

	if (!str)
		return (FALSE);
	quoteless_str = get_quoteless_str(str);
	if (!quoteless_str)
		return (TRUE);
	if (lexer && !lexer->args)
	{
		if (initialize_arguments(quoteless_str, lexer))
			return (free(quoteless_str), TRUE);
	}
	else
	{
		lexer->args = ft_append_to_string_array(lexer->args, quoteless_str);
		if (!lexer->args)
			return (free(quoteless_str), TRUE);
	}
	return (FALSE);
}
