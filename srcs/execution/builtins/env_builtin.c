/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 04:03:22 by nicolas           #+#    #+#             */
/*   Updated: 2023/05/09 22:33:30 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_bool	env_builtin(t_lexer *lexer, char ***envp)
{
	size_t	len;

	if (!lexer)
		return (FALSE);
	if (!envp || !*envp)
		return (g_status = general_failure, TRUE);
	len = ft_strarrlen((const char **)lexer->args);
	if (len > 1)
	{
		errno = E2BIG;
		return (perror("env"), g_status = misuse_of_shell_builtins, FALSE);
	}
	put_env(*envp);
	return (g_status = success, FALSE);
}
