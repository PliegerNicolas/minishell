/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:39:19 by nicolas           #+#    #+#             */
/*   Updated: 2023/04/16 17:37:50 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static char	*get_quoteless_str(const char *str)
{
	char	*quoteless_str;

	if (!str)
		return (NULL);
	quoteless_str = ft_strdup(str);
	if (!quoteless_str)
		return (perror_malloc("@quoteless_str (srcs/parsing/set_options.c #get_\
quoteless_str)"), NULL);
	quoteless_str = remove_quotes(quoteless_str, none);
	if (!quoteless_str)
		return (NULL);
	return (quoteless_str);
}

static char	**get_paths(char ***envp)
{
	char	**paths;
	size_t	i;

	if (!*envp)
		return (NULL);
	i = 0;
	while (ft_strncmp((*envp)[i], "PATH", 4) != 0)
		i++;
	paths = ft_split((*envp)[i] + 5, ':');
	if (!paths)
		return (perror_malloc("@paths (srcs/parsing/set_exec.c #get_paths)"),
			NULL);
	return (paths);
}

static char	*set_path(char *paths_section, char *cmd)
{
	char	*path;
	char	*temp_path;

	temp_path = ft_strjoin(paths_section, "/");
	if (!temp_path)
		return (perror_malloc("@temp_path (srcs/parsing/set_exec.c \
#set_path)"), NULL);
	path = ft_strjoin(temp_path, cmd);
	free(temp_path);
	if (!path)
		return (perror_malloc("@path (srcs/parsing/set_exec.c \
#set_path)"), NULL);
	return (path);
}

static char	*get_path(char *cmd, char ***envp)
{
	char	**paths;
	char	*path;
	size_t	i;

	if (!cmd)
		return (NULL);
	if (is_builtin(cmd))
		return (cmd);
	paths = get_paths(envp);
	if (!paths)
		return (free(cmd), NULL);
	i = 0;
	while (paths[i])
	{
		path = set_path(paths[i++], cmd);
		if (!path)
			return (free_str_arr(paths), free(cmd), NULL);
		if (access(path, F_OK) == 0)
			return (free_str_arr(paths), free(cmd), path);
		free(path);
	}
	return (free_str_arr(paths), cmd);
}

t_bool	set_exec(const char *str, t_lexer *lexer, t_bool *prev_is_redir,
	char ***envp)
{
	char	*quoteless_str;

	if (!str)
		return (FALSE);
	quoteless_str = get_quoteless_str(str);
	if (!quoteless_str)
		return (TRUE);
	if (*quoteless_str == '-' || *quoteless_str == '<' || *quoteless_str == '>')
	{
		lexer->exec = ft_strdup("");
		if (!lexer->exec)
			return (TRUE);
		if (*quoteless_str == '-')
			if (set_options(str, lexer))
				return (free(quoteless_str), TRUE);
		if (set_redirection(str, lexer, prev_is_redir))
			return (free(quoteless_str), TRUE);
		return (free(quoteless_str), FALSE);
	}
	lexer->exec = get_path(quoteless_str, envp);
	if (!lexer->exec)
		return (TRUE);
	return (FALSE);
}
