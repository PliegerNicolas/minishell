/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 16:08:05 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/28 00:05:46 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	perror_command_not_found(void)
{
	set_write_color(RED, STDERR);
	ft_putendl_fd("Command not found.", STDERR);
	reset_write_color(STDERR);
}

void	perror_invalid_options(void)
{
	set_write_color(RED, STDERR);
	ft_putendl_fd("Invalid option(s).", STDERR);
	reset_write_color(STDERR);
}
