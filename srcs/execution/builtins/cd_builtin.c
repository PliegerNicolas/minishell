/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 19:07:31 by nicolas           #+#    #+#             */
/*   Updated: 2023/04/26 19:05:11 by nplieger         ###   ########.fr       */
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

static t_bool	change_directory(char *path, char ***envp)
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
	oldpwd = get_env_var("PWD", (const char **)*envp);
	if (chdir(path) == -1)
		return (perror("chdir"), free(oldpwd), TRUE);
	if (!getcwd(newpwd, sizeof(newpwd)))
		return (free(oldpwd), TRUE);
	if (oldpwd)
		*envp = set_env_var("OLDPWD", oldpwd, *envp);
	if (!*envp)
		return (free(oldpwd), TRUE);
	*envp = set_env_var("PWD", newpwd, *envp);
	if (!*envp)
		return (free(oldpwd), TRUE);
	return (free(oldpwd), FALSE);
}

t_bool	cd_builtin(t_lexer *lexer, char ***envp)
{
	size_t	len;

	if (!lexer)
		return (FALSE);
	len = ft_strarrlen((const char **)lexer->args);
	if (len > 2)
	{
		errno = E2BIG;
		return (perror("cd"), g_status = misuse_of_shell_builtins, TRUE);
	}
	if (change_directory(*(lexer->args + 1), envp))
		return (g_status = general_failure, TRUE);
	return (g_status = success, FALSE);
}
