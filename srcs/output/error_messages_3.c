/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 01:05:50 by nicolas           #+#    #+#             */
/*   Updated: 2023/06/04 19:52:39 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	perror_no_such_file_or_dir(char *path)
{
	set_write_color(RED, STDERR);
	ft_putstr_fd("No such file or directory : ", STDERR);
	set_write_color(WHITE, STDERR);
	ft_putstr_fd(path, STDERR);
	set_write_color(RED, STDERR);
	ft_putendl_fd(" 눈_눈", STDERR);
	set_write_color(WHITE, STDERR);
}

void	perror_heredoc(void)
{
	set_write_color(RED, STDERR);
	ft_putstr_fd("Error while writing in heredoc : ", STDERR);
	ft_putendl_fd(" ⥀.⥀", STDERR);
	set_write_color(WHITE, STDERR);
}

void	perror_heredoc_eof(char *end)
{
	ft_putstr_fd("warning: here-document delimited by end-of-file (wanted `",
		STDERR);
	ft_putstr_fd(end, STDERR);
	ft_putendl_fd("`)", STDERR);
}
