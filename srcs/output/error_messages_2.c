/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 16:08:05 by nicolas           #+#    #+#             */
/*   Updated: 2023/04/02 01:36:07 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	perror_command_not_found(void)
{
	set_write_color(RED, STDERR);
	ft_putendl_fd("Command not found. ⊙﹏⊙", STDERR);
	reset_write_color(STDERR);
}

void	perror_invalid_options(void)
{
	set_write_color(RED, STDERR);
	ft_putendl_fd("Invalid option(s). (╬ ಠ益ಠ)", STDERR);
	reset_write_color(STDERR);
}

void	perror_parse_error(void)
{
	set_write_color(RED, STDERR);
	ft_putendl_fd("Parse error. ( ಠ ʖ̯ ಠ)", STDERR);
	reset_write_color(STDERR);
}

void	perror_file(void)
{
	set_write_color(RED, STDERR);
	ft_putendl_fd("Error on file manipulation. （　ﾟДﾟ）", STDERR);
	reset_write_color(STDERR);
}
