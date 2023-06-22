/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_prefix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 22:34:36 by nicolas           #+#    #+#             */
/*   Updated: 2023/06/22 10:12:59 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static char	*get_current_working_directory(char ***envp)
{
	char	*cwd;
	char	t_cwd[1024];

	cwd = get_env_var("PWD", (const char **)*envp);
	if (!cwd)
	{
		if (getcwd(t_cwd, sizeof(t_cwd)))
			cwd = ft_strdup(t_cwd);
		else
			cwd = ft_strdup(".");
		if (!cwd)
			return (perror_malloc("@cwd (srcs/output/prompt_prefix.c #get_curre\
nt_working_directory)"), NULL);
	}
	return (cwd);
}

static t_bool	get_home_path(char **home_path, char ***envp)
{
	char	*user;

	*home_path = get_env_var("HOME", (const char **)*envp);
	if (!*home_path)
	{
		user = get_env_var("USER", (const char **)*envp);
		if (!user)
		{
			user = get_env_var("USERNAME", (const char **)*envp);
			if (!user)
			{
				user = get_env_var("LOGNAME", (const char **)*envp);
				if (!user)
					return (FALSE);
			}
		}
		*home_path = ft_strjoin("/home/", user);
		free(user);
		if (!*home_path)
			return (perror_malloc("@*home_path (srcs/output/prompt_prefix.c #ge\
t_home_path)"), TRUE);
	}
	return (FALSE);
}

static char	*trim_path(char *path)
{
	char	*new_path;
	size_t	index[2];

	if (!path)
		return (NULL);
	index[0] = 0;
	index[1] = 0;
	while (path[index[0] + index[1]])
	{
		if (path[index[0] + index[1]] && path[index[0] + index[1]] == '/')
			index[1]++;
		while (path[index[0] + index[1]] && path[index[0] + index[1]] != '/')
			index[1]++;
		if (path[index[0] + index[1]] == '/')
		{
			index[0] += index[1];
			index[1] = 0;
		}
	}
	if (path[index[0]] == '/' && path[index[0] + 1])
		index[0]++;
	new_path = ft_substr(path, index[0], ft_strlen(path + index[0]));
	if (!new_path)
		return (perror_malloc("@new_path (srcs/output/prompt_prefix.c #trim_pat\
h)"), free(path), NULL);
	return (free(path), new_path);
}

static char	*beautify_prompt(char *prompt)
{
	char	*new_prompt;
	size_t	len;

	prompt = trim_path(prompt);
	if (!prompt)
		return (NULL);
	len = ft_strlen(prompt) + 1 + ft_strlen(WHITE) + (ft_strlen(RED) * 3)
		+ ft_strlen("➜  ") + ft_strlen(" ¤ ");
	new_prompt = ft_calloc(len, sizeof(*new_prompt));
	if (!new_prompt)
		return (perror_malloc("@new_prompt (srcs/output/prompt_prefix.c #beauti\
fy_prompt)"), free(prompt), NULL);
	ft_strlcat(new_prompt, "\001➜\002  ", len);
	ft_strlcat(new_prompt, CYAN, len);
	ft_strlcat(new_prompt, prompt, len);
	ft_strlcat(new_prompt, YELLOW, len);
	ft_strlcat(new_prompt, " ¤ ", len);
	ft_strlcat(new_prompt, WHITE, len);
	if (prompt && g_status == success)
		ft_putstr_fd(GREEN, STDOUT);
	else if (prompt && g_status != success)
		ft_putstr_fd(RED, STDOUT);
	return (free(prompt), new_prompt);
}

char	*prompt_prefix(char ***envp)
{
	char	*prompt;
	char	*home_path;

	prompt = get_current_working_directory(envp);
	if (!prompt)
		return (NULL);
	home_path = NULL;
	if (get_home_path(&home_path, envp))
		return (free(prompt), NULL);
	if (home_path)
	{
		if (ft_strncmp(prompt, home_path, ft_strlen(home_path) + 1) == 0)
		{
			free(prompt);
			prompt = ft_strdup("~");
			if (!prompt)
				return (perror_malloc("@prompt (srcs/output/prompt_prefix.c #pr\
ompt_prefix)"), free(home_path), NULL);
		}
		free(home_path);
	}
	prompt = beautify_prompt(prompt);
	if (!prompt)
		return (NULL);
	return (prompt);
}
