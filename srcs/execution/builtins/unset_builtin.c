/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 23:31:30 by nicolas           #+#    #+#             */
/*   Updated: 2023/04/19 18:46:18 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_bool	unset_env_variables(char **unset_args, char ***envp)
{
	size_t	i;

	if (!unset_args)
		return (FALSE);
	i = 0;
	while (unset_args[i])
	{
		*envp = remove_env_var(unset_args[i++], *envp);
		if (!*envp)
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
	if (len <= 1)
	{
		if (len <= 1)
			errno = EINVAL;
		perror("unset");
		return (g_status = command_invoked_cannot_execute, TRUE);
	}
	if (unset_env_variables(lexer->args + 1, envp))
		return (g_status = general_failure, TRUE);
	return (g_status = success, FALSE);
}
