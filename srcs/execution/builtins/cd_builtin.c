/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 19:07:31 by nicolas           #+#    #+#             */
/*   Updated: 2023/05/09 18:56:44 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/*
static char	*substitute_variable(char *line, const char *substr,
	const char *replacement)
{
	char	*new_line;
	char	*pos;
	size_t	lens[3];

	if (!line || !substr || !replacement)
		return (line);
	lens[0] = ft_strlen(line);
	pos = ft_strnstr(line, substr, lens[0]);
	lens[1] = ft_strlen(substr);
	lens[2] = ft_strlen(replacement);
	new_line = malloc((lens[0] + lens[2] - lens[1] + 1) * sizeof(*new_line));
	if (!new_line)
	{
		perror_malloc("@variable_name (srcs/parsing/substitute_variables.c #sub\
stitute_variables)");
		return (free(line), NULL);
	}
	ft_memcpy(new_line, line, pos - line);
	ft_memcpy(new_line + (pos - line), replacement, lens[2]);
	ft_memcpy(new_line + (pos - line) + lens[2], pos + lens[1],
		line + lens[0] - (pos + lens[1]));
	new_line[lens[0] + (lens[2] - lens[1])] = '\0';
	return (free(line), new_line);
}
*/

static t_bool	parse_cd_path(char **path, char ***envp)
{
	char	*home_path;
	char	*user;

	if (!(*path) || ((*path)[0] == '~' && (!(*path)[1] || (*path)[1] == '/')))
	{
		home_path = get_env_var("HOME", (const char **)*envp);
		if (!home_path)
		{
			if (!(*path))
			{
				ft_putendl_fd("cd: HOME not set", STDERR);
				return (free(*path), TRUE);
			}
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
						return (free(*path), TRUE);
					}
				}
			}
			home_path = ft_strjoin("/home/", user);
			free(user);
			if (!home_path)
				return (free(*path), FALSE);
		}
	}
	else
		home_path = NULL;
	if (home_path)
	{
		if (!*path)
			*path = home_path;
		else
		{
			*path = replace_first(*path, "~", home_path);
			free(home_path);
			if (!*path)
				return (FALSE);
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
		return (perror_malloc("test"), g_status = general_failure, TRUE);
	if (change_directory(path, envp))
		return (free(path), g_status = general_failure, TRUE);
	return (free(path), g_status = success, FALSE);
}

/*
static char	*substitute_variable(char *line, const char *substr,
	const char *replacement)
{
	char	*new_line;
	char	*pos;
	size_t	lens[3];

	if (!line || !substr || !replacement)
		return (line);
	lens[0] = ft_strlen(line);
	pos = ft_strnstr(line, substr, lens[0]);
	lens[1] = ft_strlen(substr);
	lens[2] = ft_strlen(replacement);
	new_line = malloc((lens[0] + lens[2] - lens[1] + 1) * sizeof(*new_line));
	if (!new_line)
	{
		perror_malloc("@variable_name (srcs/parsing/substitute_variables.c #sub\
stitute_variables)");
		return (free(line), NULL);
	}
	ft_memcpy(new_line, line, pos - line);
	ft_memcpy(new_line + (pos - line), replacement, lens[2]);
	ft_memcpy(new_line + (pos - line) + lens[2], pos + lens[1],
		line + lens[0] - (pos + lens[1]));
	new_line[lens[0] + (lens[2] - lens[1])] = '\0';
	return (free(line), new_line);
}

static char *set_cd_path(const char *s, char ***envp)
{
	char	*path;
	char	*home_path;
	char	*user;

	home_path = NULL;
	if (!s || ft_strchr(s, '~'))
	{
		home_path = get_env_var("HOME", (const char **)*envp);
		if (!home_path)
		{
			user = get_env_var("USER", (const char **)*envp);
			if (!user)
			{
				user = get_env_var("LOGNAME", (const char **)*envp);
				if (!user)
				{
					ft_putendl_fd("cd: No home directory found", STDERR);
					return (ft_strdup(""));
				}
			}
			home_path = ft_strjoin("/home/", user);
			free(user);
			if (!home_path)
				return (NULL);
		}
	}
	if (home_path)
	{
		if (!s)
			path = home_path;
		else
		{
			path = ft_strdup(s);
			if (!path)
				return (free(home_path), NULL);
			if (*path == '~' && *(path + 1) && *(path + 1) != '~')
			{
				path = substitute_variable(path, "~", home_path);
				if (!path)
					return (free(home_path), NULL);
			}
			free(home_path);
		}
	}
	else
	{
		path = ft_strdup(s);
		if (!path)
			return (NULL);
	}
	return (path);
}

t_bool	cd_builtin(t_lexer *lexer, char ***envp)
{
	char	*path;
	size_t	len;

	if (!lexer)
		return (FALSE);
	len = ft_strarrlen((const char **)lexer->args);
	if (len > 2)
	{
		errno = E2BIG;
		return (perror("cd"), g_status = misuse_of_shell_builtins, FALSE);
	}

	path = set_cd_path(lexer->args[1], envp);
	if (!path)
		return (perror_malloc("test"), g_status = general_failure, TRUE);
	else if (ft_strncmp(path, "", 1) == 0)
		return (free(path), g_status = general_failure, FALSE);
	printf("%s\n", path);

	return (free(path), g_status = success, FALSE);
}
*/

/*
static char	*get_home_path(t_bool tild, char ***envp)
{
	char	*path;
	char	*user;

	path = get_env_var("HOME", (const char **)*envp);
	if (!path)
	{
		if (!tild)
		{
			user = get_env_var("USER", (const char **)*envp);
			if (!user)
			{
				user = get_env_var("LOGNAME", (const char **)*envp);
				if (!user)
				{
					path = ft_strdup("");
					if (!path)
						return (NULL);
					return (path);
				}
			}
			path = ft_strjoin("/home/", user);
			free(user);
		}
		else
		{
			path = ft_strdup("");
			ft_putendl_fd("cd: HOME not set", STDERR);
		}
	}
	if (!path)
		return (NULL);
	return (path);
}

static char	*substitute_variable(char *line, const char *substr,
	const char *replacement)
{
	char	*new_line;
	char	*pos;
	size_t	lens[3];

	if (!line || !substr || !replacement)
		return (line);
	lens[0] = ft_strlen(line);
	pos = ft_strnstr(line, substr, lens[0]);
	lens[1] = ft_strlen(substr);
	lens[2] = ft_strlen(replacement);
	new_line = malloc((lens[0] + lens[2] - lens[1] + 1) * sizeof(*new_line));
	if (!new_line)
	{
		perror_malloc("@variable_name (srcs/parsing/substitute_variables.c #sub\
stitute_variables)");
		return (free(line), NULL);
	}
	ft_memcpy(new_line, line, pos - line);
	ft_memcpy(new_line + (pos - line), replacement, lens[2]);
	ft_memcpy(new_line + (pos - line) + lens[2], pos + lens[1],
		line + lens[0] - (pos + lens[1]));
	new_line[lens[0] + (lens[2] - lens[1])] = '\0';
	return (free(line), new_line);
}

t_bool	cd_builtin(t_lexer *lexer, char ***envp)
{
	char	*path;
	char	*home_path;
	size_t	len;

	if (!lexer)
		return (FALSE);
	len = ft_strarrlen((const char **)lexer->args);
	if (len > 2)
	{
		errno = E2BIG;
		return (perror("cd"), g_status = misuse_of_shell_builtins, FALSE);
	}
	// find home/path from ~
	while (lexer->args[1] && ft_strchr(lexer->args[1], '~'))
	{
		home_path = get_home_path(TRUE, envp);
		if (!home_path)
			return (perror_malloc("test"), g_status = general_failure, TRUE);
		else if (ft_strncmp(home_path, "", 1) == 0)
			return (free(home_path), g_status = general_failure, FALSE);
		lexer->args[1] = substitute_variable(lexer->args[1], "~", home_path);
		free(home_path);
		if (!lexer->args[1])
			return (TRUE);
	}
	if (lexer->args[1])
		path = ft_strdup(lexer->args[1]);
	else
		path = get_home_path(FALSE, envp);
	if (path && ft_strncmp(path, "", 1) == 0)
	{
		free(path);
		path = ft_strdup("/");
	}
	if (!path)
		return (perror_malloc("test2"), g_status = general_failure, TRUE);
	printf("%s\n", path);
	(void)envp;
	return (g_status = success, FALSE);
}
*/

/*
static t_bool	parse_cd_path(char **path, const char *s, char ***envp)
{
	char	*user;

	if (!s)
	{
		*path = get_env_var("HOME", (const char **)*envp);
		if (!path || !*path)
		{
			ft_putendl_fd("cd: HOME not set", STDERR);
			return (g_status = general_failure, FALSE);
		}
	}
	else if (ft_strncmp(s, "~", 2) == 0)
	{
		if (test(path, envp))
			return (FALSE);
		*path = get_env_var("HOME", (const char **)*envp);
		if (!path || !*path)
		{
			user = get_env_var("USER", (const char **)*envp);
			if (!user)
			{
				user = get_env_var("LOGNAME", (const char **)*envp);
				if (!user)
				{
					ft_putendl_fd("cd: can't cd to ~: No such file or directory", STDERR);
					return (g_status = general_failure, FALSE);
				}
			}
			*path = ft_strjoin("/home/", user);
			free(user);
		}
	}
	else
		*path = ft_strdup(s);
	if (!path || !*path)
		return (perror_malloc("@path (srcs/execuion/builtins/cd_builtin.c #chan\
ge_directory"), g_status = general_failure, TRUE);
	return (FALSE);
}

static t_bool	change_directory(char *path, char ***envp)
{
	char 	oldpwd[1024];
	char	cwd[1024];

	if (!path)
		return (FALSE);
	if (!getcwd(oldpwd, sizeof(oldpwd)))
		return (perror("getcwd"), free(path), TRUE);
	if (chdir(path) == -1)
		return (perror("chdir"), free(path), FALSE);
	free(path);
	if (!getcwd(cwd, sizeof(cwd)))
		return (perror("getcwd"), TRUE);
	*envp = set_env_var("OLDPWD", oldpwd, *envp);
	if (!envp || !*envp)
		return (perror_malloc("@envp (srcs/execuion/builtins/cd_builtin.c #chan\
ge_directory"), g_status = general_failure, TRUE);
	*envp = set_env_var("PWD", cwd, *envp);
	if (!envp || !*envp)
		return (perror_malloc("@envp (srcs/execuion/builtins/cd_builtin.c #chan\
ge_directory"), g_status = general_failure, TRUE);
	return (FALSE);
}

t_bool	cd_builtin(t_lexer *lexer, char ***envp)
{
	char	*path;
	size_t	len;

	if (!lexer)
		return (FALSE);
	len = ft_strarrlen((const char **)lexer->args);
	if (len > 2)
	{
		errno = E2BIG;
		return (perror("cd"), g_status = misuse_of_shell_builtins, FALSE);
	}
	path = NULL;
	if (parse_cd_path(&path, lexer->args[1], envp))
		return (TRUE);
	if (change_directory(path, envp))
		return (TRUE);
	return (g_status = success, FALSE);
}
*/
