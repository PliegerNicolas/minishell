/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 19:07:31 by nicolas           #+#    #+#             */
/*   Updated: 2023/04/04 19:24:48 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static char	*get_home_directory(void)
{
	char	*home_dir;

	home_dir = getenv("HOME");
	if (!home_dir)
	{
		printf("Home environment variable is not set.\n"); // temp
		g_status = command_invoked_cannot_execute;
		return (NULL);
	}
	return (home_dir);
}

static t_bool	change_directory(char *path)
{
	if (!path || ft_strncmp(path, "~", 2) == 0)
	{
		path = get_home_directory();
		if (!path)
			return (TRUE);
	}
	if (chdir(path) != 0)
	{
		printf ("chdir() error.\n"); // temp
		return (TRUE);
	}
	return (FALSE);
}

t_bool	cd_builtin(t_lexer *lexer, char **envp)
{
	if (!envp)
		return (g_status = command_invoked_cannot_execute, TRUE);
	if (lexer->options)
		return (g_status = misuse_of_shell_builtins, TRUE);
	change_directory(*(lexer->args + 1));
	return (FALSE);
}
