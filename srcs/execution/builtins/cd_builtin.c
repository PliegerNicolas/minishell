/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 19:07:31 by nicolas           #+#    #+#             */
/*   Updated: 2023/04/05 15:13:21 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static char	*get_home_directory(void)
{
	char	*home_dir;

	home_dir = getenv("HOME");
	if (!home_dir)
	{
		perror_no_such_file_or_dir("/home/user");
		g_status = command_invoked_cannot_execute;
		return (NULL);
	}
	return (home_dir);
}

static t_bool	change_directory(char *path, char **envp)
{
	char	*oldpwd;
	char	newpwd[1024];

	if (!path || ft_strncmp(path, "~", 2) == 0)
	{
		if (path)
			free(path);
		path = get_home_directory();
		if (!path)
			return (TRUE);
	}
	oldpwd = get_env_var("PWD", (const char **)envp);
	if (!oldpwd)
		return (TRUE);
	if (chdir(path) == -1)
		return (g_status = general_failure, perror_no_suck_file_or_dir(path),
			free(oldpwd), TRUE);
	getcwd(newpwd, sizeof(newpwd));
	envp = set_env_var("OLDPWD", oldpwd, envp);
	if (!envp)
		return (g_status = general_failure, free(oldpwd), TRUE);
	envp = set_env_var("PWD", newpwd, envp);
	if (!envp)
		return (g_status = general_failure, free(oldpwd), TRUE);
	return (free(oldpwd), FALSE);
}

t_bool	cd_builtin(t_lexer *lexer, char **envp)
{
	if (lexer->options)
		return (perror_unexpected_option(),
			g_status = misuse_of_shell_builtins, TRUE);
	if (lexer && *(lexer->args + 2))
		return (perror_too_many_arguments(), g_status = general_failure, TRUE);
	if (change_directory(*(lexer->args + 1), envp))
		return (TRUE);
	return (FALSE);
}
