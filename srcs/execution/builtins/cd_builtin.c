/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 19:07:31 by nicolas           #+#    #+#             */
/*   Updated: 2023/05/09 23:41:31 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static char	*get_username(char ***envp)
{
	char	*user;

	user = get_env_var("USER", (const char **)*envp);
	if (!user)
	{
		user = get_env_var("USERNAME", (const char **)*envp);
		if (!user)
		{
			user = get_env_var("LOGNAME", (const char **)*envp);
			if (!user)
			{
				ft_putendl_fd("cd: No home directory found", STDERR);
				return (NULL);
			}
		}
	}
	return (user);
}

static t_bool	get_home_path(char **home_path, char **path, char ***envp)
{
	char	*user;

	*home_path = get_env_var("HOME", (const char **)*envp);
	if (!*home_path)
	{
		if (!(*path))
		{
			ft_putendl_fd("cd: HOME not set", STDERR);
			return (TRUE);
		}
		user = get_username(envp);
		if (!user)
			return (TRUE);
		*home_path = ft_strjoin("/home/", user);
		free(user);
		if (!*home_path)
			return (FALSE);
	}
	return (FALSE);
}

static t_bool	parse_cd_path(char **path, char ***envp)
{
	char	*home_path;

	home_path = NULL;
	if (!(*path) || ((*path)[0] == '~' && (!(*path)[1] || (*path)[1] == '/')))
	{
		if (get_home_path(&home_path, path, envp))
			return (free(*path), *path = NULL, TRUE);
		if (!home_path)
			return (free(*path), *path = NULL, FALSE);
	}
	if (home_path)
	{
		if (!*path)
			*path = home_path;
		else
		{
			*path = replace_first(*path, "~", home_path);
			free(home_path);
		}
	}
	return (FALSE);
}

static t_bool	change_directory(char *path, char ***envp)
{
	char	oldpwd[1024];
	char	cwd[1024];

	if (!path)
		return (FALSE);
	if (!getcwd(oldpwd, sizeof(oldpwd)))
		return (perror("getcwd"), TRUE);
	if (chdir(path) == -1)
		return (perror("chdir"), FALSE);
	if (!getcwd(cwd, sizeof(cwd)))
		return (perror("getcwd"), TRUE);
	*envp = set_env_var("OLDPWD", oldpwd, *envp);
	if (!envp || !*envp)
		return (perror_malloc("@envp (srcs/execuion/builtins/cd_builtin.c #chan\
ge_directory"), TRUE);
	*envp = set_env_var("PWD", cwd, *envp);
	if (!envp || !*envp)
		return (perror_malloc("@envp (srcs/execuion/builtins/cd_builtin.c #chan\
ge_directory"), TRUE);
	return (FALSE);
}

t_bool	cd_builtin(t_lexer *lexer, char ***envp)
{
	char	*path;
	size_t	len;

	if (!lexer)
		return (FALSE);
	if (!envp || !*envp)
		return (g_status = general_failure, TRUE);
	len = ft_strarrlen((const char **)lexer->args);
	if (len > 2)
	{
		errno = E2BIG;
		return (perror("cd"), g_status = misuse_of_shell_builtins, FALSE);
	}
	if (lexer->args[1])
		path = ft_strdup(lexer->args[1]);
	else
		path = NULL;
	if (parse_cd_path(&path, envp))
		return (g_status = general_failure, FALSE);
	else if (!path)
		return (perror_malloc("@path (srcs/execuion/builtins/cd_builtin.c #cd_b\
uiltin"), g_status = general_failure, TRUE);
	if (change_directory(path, envp))
		return (free(path), g_status = general_failure, TRUE);
	return (free(path), g_status = success, FALSE);
}
