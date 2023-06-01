/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:39:19 by nicolas           #+#    #+#             */
/*   Updated: 2023/06/01 13:56:24 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

// Verifier si le fichier/dossier existe localement ?
t_bool	set_exec(char *cmd, t_lexer *lexer, char ***envp)
{
	if (!lexer)
		return (TRUE);
	if (!cmd)
		return (TRUE);
	lexer->exec = cmd;
	lexer->exec = get_path(lexer->exec, envp);
	if (!lexer->exec)
		return (TRUE);
	return (FALSE);
}
