/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 20:36:38 by nicolas           #+#    #+#             */
/*   Updated: 2023/04/11 20:37:35 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_bool	builtin_execution(t_lexer *lexer, char ***envp)
{
	if (!lexer)
		return (FALSE);
	printf("Builtin exec\n");
	(void)envp;
	return (FALSE);
}
