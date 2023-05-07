/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:39:19 by nicolas           #+#    #+#             */
/*   Updated: 2023/05/07 17:41:40 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_bool	set_exec(const char *str, t_lexer *lexer, t_bool *prev_is_redir,
	char ***envp)
{
	char	*quoteless_str;

	if (!str)
		return (FALSE);
	quoteless_str = get_quoteless_str(str);
	if (!quoteless_str)
		return (TRUE);
	if (*quoteless_str == '-' || *quoteless_str == '<' || *quoteless_str == '>')
	{
		lexer->exec = ft_strdup("");
		if (!lexer->exec)
			return (TRUE);
		if (*quoteless_str == '-')
			if (set_options(str, lexer))
				return (free(quoteless_str), TRUE);
		if (set_redirection(str, lexer, prev_is_redir, envp))
			return (free(quoteless_str), TRUE);
		return (free(quoteless_str), FALSE);
	}
	lexer->exec = get_path(quoteless_str, envp);
	if (!lexer->exec)
		return (TRUE);
	return (FALSE);
}
