/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_prefix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 22:34:36 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/10 13:47:19 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static char	*parse_prompt_prefix(char *cwd)
{
	char	*parsed_cwd;
	size_t	start;
	size_t	end;

	start = 0;
	end = 0;
	while (cwd[end])
		if (cwd[end++] == '/')
			start = end;
	parsed_cwd = ft_substr(cwd, start, end);
	free(cwd);
	return (parsed_cwd);
}

static char	*compose_prompt_prefix(char *cwd)
{
	char	*prompt_prefix;
	char	*temp;

	if (!cwd)
		return (NULL);
	temp = ft_strjoin("➜  \033[1;36m", cwd);
	free(cwd);
	if (!temp)
		return (NULL);
	prompt_prefix = ft_strjoin(temp, "\033[1;33m ✗ \033[0m");
	free(temp);
	if (!prompt_prefix)
		return (NULL);
	return (prompt_prefix);	
}

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
	/*
	if (status == success)
		set_write_color(GREEN, STDOUT);
	else
		set_write_color(RED, STDOUT);
	ft_putstr_fd("➜  ", STDOUT);
	set_write_color(CYAN, STDOUT);
	ft_putstr_fd(cwd, STDOUT);
	set_write_color(YELLOW, STDOUT);
	ft_putstr_fd(" ✗", STDOUT);
	reset_write_color(STDOUT);
	*/
}
