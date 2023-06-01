/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_arguments.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:47:14 by nicolas           #+#    #+#             */
/*   Updated: 2023/06/01 13:37:27 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static t_bool	initialize_arguments(t_lexer *lexer)
{
	if (lexer && lexer->args)
		return (FALSE);
	lexer->args = malloc(1 * sizeof(*lexer->args));
	if (!lexer->args)
		return (perror_malloc("@lexer->args (srcs/parsing/set_arguments.c #init\
ialize_arguments)"), TRUE);
	lexer->args[0] = NULL;
	return (FALSE);
}

t_bool	set_arguments(const char *str, t_lexer *lexer, char ***envp)
{
	char	*quoteless_str;

	if (!str)
		return (FALSE);
	quoteless_str = get_quoteless_str(str);
	if (!quoteless_str)
		return (TRUE);
	if (!lexer->exec)
	{
		if (set_exec(quoteless_str, lexer, envp))
			return (free(quoteless_str), TRUE);
		if (initialize_arguments(lexer))
			return (TRUE);
	}
	else
	{
		lexer->args = ft_append_to_string_array(lexer->args, quoteless_str);
		if (!lexer->args)
			return (free(quoteless_str), TRUE);
	}
	return (FALSE);
}
