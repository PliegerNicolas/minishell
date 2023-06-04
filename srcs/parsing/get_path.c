/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 17:59:27 by nicolas           #+#    #+#             */
/*   Updated: 2023/06/04 12:24:29 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static char	**get_paths(char ***envp)
{
	char	**paths;
	size_t	i;

	if (!*envp)
		return (NULL);
	i = 0;
	while ((*envp)[i] && ft_strncmp((*envp)[i], "PATH", 4) != 0)
		i++;
	if (!(*envp)[i])
		return (NULL);
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

char	*get_path(char *cmd, char ***envp)
{
	char	**paths;
	char	*path;
	size_t	i;

	if (!cmd)
		return (NULL);
	if (is_builtin(cmd))
		return (cmd);
	if (access(cmd, X_OK) == 0)
		return (cmd);
	paths = get_paths(envp);
	if (!paths)
		return (cmd);
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
