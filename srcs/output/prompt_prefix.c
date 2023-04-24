/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_prefix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 22:34:36 by nicolas           #+#    #+#             */
/*   Updated: 2023/04/24 12:56:27 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static char	*get_user(char ***envp)
{
	char	*user;

	user = get_env_var("USER", (const char **)*envp);
	if (!user)
	{
		*envp = set_env_var("USER", "username", *envp);
		free(user);
		if (!envp)
			return (NULL);
		user = get_env_var("USER", (const char **)*envp);
	}
	if (!user)
		return (NULL);
	return (user);
}

/*
	delimiters[0] = start;
	delimiters[1] = end;
*/
static char	*set_path(char *path, char *parsed_path)
{
	size_t	delimiters[2];

	if (ft_strncmp(path, parsed_path, ft_strlen(parsed_path) + 1) == 0)
	{
		free(parsed_path);
		parsed_path = ft_strdup("~");
		if (!parsed_path)
			return (NULL);
		return (parsed_path);
	}
	free(parsed_path);
	if (ft_strncmp(path, "/", 2) == 0)
		parsed_path = ft_strdup("/");
	else
	{
		delimiters[0] = 0;
		delimiters[1] = 0;
		while (path[delimiters[1]])
			if (path[delimiters[1]++] == '/')
				delimiters[0] = delimiters[1];
		parsed_path = ft_substr(path, delimiters[0], delimiters[1]);
	}
	if (!parsed_path)
		return (NULL);
	return (parsed_path);
}

/*
	This function gets the last element of a string splitted by '/'.
	It's purpose is to get the name of the last directory of the given path.
	If the given path is /home/USER. It returns ~.

	@delimiters[0] = start of substr.
	@delimiters[1] = end of substr.
*/
static char	*parse_prompt_prefix(char *path, char ***envp)
{
	char	*parsed_path;
	char	*user;

	user = get_user(envp);
	if (!user)
		return (free(path), NULL);
	parsed_path = ft_strjoin("/home/", user);
	free(user);
	if (!parsed_path)
		return (free(path), NULL);
	parsed_path = set_path(path, parsed_path);
	if (!parsed_path)
		return (free(path), NULL);
	return (free(path), parsed_path);
}

/*
	This composes the "prompt_prefix".
	It should look like : "➜  [dir_name] ¤ "
*/
static char	*compose_prompt_prefix(char *dir_name)

{
	char	*prompt_prefix;
	size_t	len;

	if (!dir_name)
		return (NULL);
	len = (ft_strlen(RED) * 3) + ft_strlen(WHITE) + ft_strlen("➜  ")
		+ ft_strlen(" ¤ ") + ft_strlen(dir_name) + 1;
	prompt_prefix = malloc(len * sizeof(*prompt_prefix));
	if (!prompt_prefix)
		return (NULL);
	*prompt_prefix = '\0';
	ft_strlcat(prompt_prefix, "\001➜\002  ", len);
	ft_strlcat(prompt_prefix, CYAN, len);
	ft_strlcat(prompt_prefix, dir_name, len);
	ft_strlcat(prompt_prefix, YELLOW, len);
	ft_strlcat(prompt_prefix, " ¤ ", len);
	ft_strlcat(prompt_prefix, WHITE, len);
	return (free(dir_name), prompt_prefix);
}

/*
	This function creates the "prompt_prefix". A small and colored message to
	indicate when prompt is open.
*/
char	*prompt_prefix(char ***envp)
{
	char	*cwd;

	cwd = malloc((BUFFER_SIZE + 1) * sizeof(*cwd));
	if (!cwd)
		return (NULL);
	if (!getcwd(cwd, BUFFER_SIZE))
		return (free(cwd), NULL);
	cwd = parse_prompt_prefix(cwd, envp);
	if (!cwd)
		return (NULL);
	if (g_status == success)
		ft_putstr_fd(GREEN, STDOUT);
	else
		ft_putstr_fd(RED, STDOUT);
	cwd = compose_prompt_prefix(cwd);
	return (cwd);
}
