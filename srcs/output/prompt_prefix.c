/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_prefix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 22:34:36 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/10 13:52:32 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/*
	This function gets the last element of a string splitted by '/'.
	It's purpose is to get the name of the last directory of the given path.
*/
static char	*parse_prompt_prefix(char *path)
{
	char	*parsed_path;
	size_t	start;
	size_t	end;

	start = 0;
	end = 0;
	while (path[end])
		if (path[end++] == '/')
			start = end;
	parsed_path = ft_substr(path, start, end);
	free(path);
	return (parsed_path);
}

/*
	This composes the "prompt_prefix".
	It should look like : "➜  [dir_name] ✗"
*/
static char	*compose_prompt_prefix(char *dir_name)
{
	char	*prompt_prefix;
	char	*temp;

	if (!dir_name)
		return (NULL);
	temp = ft_strjoin("➜  \033[1;36m", dir_name);
	free(dir_name);
	if (!temp)
		return (NULL);
	prompt_prefix = ft_strjoin(temp, "\033[1;33m ✗ \033[0m");
	free(temp);
	if (!prompt_prefix)
		return (NULL);
	return (prompt_prefix);
}

/*
	This function creates the "prompt_prefix". A small and colored message to
	indicate when prompt is open.
*/
char	*prompt_prefix(const enum e_status status)
{
	char	*cwd;

	cwd = malloc((BUFFER_SIZE + 1) * sizeof(*cwd));
	if (!cwd)
		return (NULL);
	getcwd(cwd, BUFFER_SIZE);
	cwd = parse_prompt_prefix(cwd);
	if (!cwd)
		return (NULL);
	if (status == success)
		ft_putstr_fd(GREEN, STDOUT);
	else
		ft_putstr_fd(RED, STDOUT);
	cwd = compose_prompt_prefix(cwd);
	return (cwd);
}
