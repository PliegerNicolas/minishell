/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_arguments.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:47:14 by nicolas           #+#    #+#             */
/*   Updated: 2023/04/02 16:59:49 by nicolas          ###   ########.fr       */
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

static t_bool	append_str_to_arguments(char *quoteless_str, t_lexer *lexer)
{
	char	**new_args;
	size_t	len;
	size_t	i;

	if (!quoteless_str || (lexer && !lexer->args))
		return (FALSE);
	len = 0;
	while (lexer->args[len])
		len++;
	new_args = malloc((len + 2) * sizeof(*new_args));
	if (!new_args)
		return (perror_malloc("@new_args (srcs/parsing/set_arguments.c #append_\
str_to_arguments)"), TRUE);
	i = 0;
	while (i < len)
	{
		new_args[i] = lexer->args[i];
		i++;
	}
	new_args[i++] = quoteless_str;
	new_args[i] = NULL;
	free(lexer->args);
	lexer->args = new_args;
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
		if (append_str_to_arguments(quoteless_str, lexer))
			return (free(quoteless_str), TRUE);
	}
	return (FALSE);
}
