/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_prefix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 22:34:36 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/18 20:06:19 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/*
	This function gets the last element of a string splitted by '/'.
	It's purpose is to get the name of the last directory of the given path.
	If the given path is /home/USER. It returns ~.
*/
static char	*parse_prompt_prefix(char *path)
{
	char	*parsed_path;
	size_t	start;
	size_t	end;

	start = 0;
	end = 0;
	parsed_path = ft_strjoin("/home/", getenv("USER"));
	if (!parsed_path)
		return (free(path), NULL);
	if (strncmp(path, parsed_path, ft_strlen(parsed_path) + 1) == 0)
	{
		free(parsed_path);
		parsed_path = ft_substr("~", 0, 1);
	}
	else
	{
		free(parsed_path);
		while (path[end])
			if (path[end++] == '/')
				start = end;
		parsed_path = ft_substr(path, start, end);
	}
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
char	*prompt_prefix(void)
{
	char	*cwd;

	cwd = malloc((BUFFER_SIZE + 1) * sizeof(*cwd));
	if (!cwd)
		return (NULL);
	getcwd(cwd, BUFFER_SIZE);
	cwd = parse_prompt_prefix(cwd);
	if (!cwd)
		return (NULL);
	if (g_status == success)
		ft_putstr_fd(GREEN, STDOUT);
	else
		ft_putstr_fd(RED, STDOUT);
	cwd = compose_prompt_prefix(cwd);
	return (cwd);
}
