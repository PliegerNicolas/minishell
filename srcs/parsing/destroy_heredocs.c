/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_heredocs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:35:58 by nicolas           #+#    #+#             */
/*   Updated: 2023/05/14 22:55:26 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static char	*get_heredoc_name(int index)
{
	char	*path;
	char	*id;

	id = ft_itoa(index);
	if (!id)
		return (NULL);
	path = ft_strjoin(".heredoc_", id);
	free(id);
	if (!path)
		return (NULL);
	return (path);
}

void	destroy_heredocs(void)
{
	char	*path;
	size_t	i;

	i = 1;
	while (1)
	{
		path = get_heredoc_name(i);
		if (!path)
		{
			g_status = exit_program;
			return ;
		}
		if (access(path, F_OK) == 0)
			unlink(path);
		else
		{
			free(path);
			break ;
		}
		free(path);
		i++;
	}
}
