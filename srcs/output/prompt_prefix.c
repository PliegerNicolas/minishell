/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_prefix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 22:34:36 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/10 13:09:20 by nicolas          ###   ########.fr       */
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

void	prompt_prefix(enum e_status status)
{
	char	*cwd;

	cwd = malloc((BUFFER_SIZE + 1) * sizeof(*cwd));
	if (!cwd)
		return ;
	getcwd(cwd, BUFFER_SIZE);
	cwd = parse_prompt_prefix(cwd);
	if (!cwd)
		return ;
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
	free(cwd);
}
