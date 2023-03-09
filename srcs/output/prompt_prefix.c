/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_prefix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 22:34:36 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/09 19:26:57 by nicolas          ###   ########.fr       */
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

void	prompt_prefix(void)
{
	char	*cwd;

	cwd = malloc((BUFFER_SIZE + 1) * sizeof(*cwd));
	if (!cwd)
		return ;
	getcwd(cwd, BUFFER_SIZE);
	cwd = parse_prompt_prefix(cwd);
	if (!cwd)
		return ;
	if (g_status == success)
		set_write_color(GREEN, 1);
	else
		set_write_color(RED, 1);
	ft_putstr_fd("➜  ", 1);
	set_write_color(CYAN, 1);
	ft_putstr_fd(cwd, 1);
	set_write_color(YELLOW, 1);
	ft_putstr_fd(" ✗", 1);
	reset_write_color(1);
	free(cwd);
}
