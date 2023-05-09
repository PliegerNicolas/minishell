/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 23:31:30 by nicolas           #+#    #+#             */
/*   Updated: 2023/05/09 23:41:39 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static t_bool	unset_env_variables(char **unset_args, char ***envp)
{
	size_t	i;

	if (!unset_args)
		return (FALSE);
	i = 0;
	while (unset_args[i])
	{
		*envp = remove_env_var(unset_args[i++], *envp);
		if (!envp || !*envp)
			return (TRUE);
	}
	return (FALSE);
}

t_bool	unset_builtin(t_lexer *lexer, char ***envp)
{
	size_t	len;

	if (!lexer)
		return (FALSE);
	len = ft_strarrlen((const char **)lexer->args);
	if (len > 1)
	{
		if (unset_env_variables(lexer->args + 1, envp))
			return (g_status = general_failure);
	}
	return (g_status = success, FALSE);
}
