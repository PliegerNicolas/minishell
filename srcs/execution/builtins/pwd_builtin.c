/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 18:59:52 by nicolas           #+#    #+#             */
/*   Updated: 2023/06/02 11:15:57 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_bool	pwd_builtin(t_lexer *lexer)
{
	char	cwd[1024];

	if (!lexer)
		return (FALSE);
	if (getcwd(cwd, sizeof(cwd)))
		ft_putendl_fd(cwd, STDOUT);
	else
		return (g_status = general_failure, TRUE);
	return (g_status = success, FALSE);
}
