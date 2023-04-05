/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 01:05:50 by nicolas           #+#    #+#             */
/*   Updated: 2023/04/05 23:36:21 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	perror_unexpected_option(void)
{
	ft_putendl_fd("No option expected. (´･_･`)", STDERR);
}

void	perror_too_many_arguments(void)
{
	ft_putendl_fd("Too many arguments. (҂◡_◡)", STDERR);
}

void	perror_not_enough_arguments(void)
{
	ft_putendl_fd("Not enough arguments. (._.)", STDERR);
}

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
