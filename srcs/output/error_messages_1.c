/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 11:30:19 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/14 02:19:21 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	perror_minishell_arguments(int nbr_args)
{
	set_write_color(RED, STDERR);
	ft_putendl_fd("Error ... (╥﹏╥)", STDERR);
	ft_putnbr_fd(nbr_args, STDERR);
	if (nbr_args == 1)
		ft_putstr_fd(" argument given ", STDERR);
	else
		ft_putstr_fd(" arguments given ", STDERR);
	ft_putendl_fd("while 0 are expected.", STDERR);
	reset_write_color(STDERR);
}

void	perror_environnement_copy(void)
{
	set_write_color(RED, STDERR);
	ft_putendl_fd("Error ... ╚(•⌂•)╝", STDERR);
	ft_putendl_fd("Environnement empty or not available.", STDERR);
	reset_write_color(STDERR);
}

void	perror_malloc(char *location)
{
	set_write_color(RED, STDERR);
	ft_putendl_fd("Error ... ( ͡° ʖ̯ ͡°)", STDERR);
	ft_putendl_fd("A memory allocation went wrong.", STDERR);
	ft_putstr_fd("See : ", STDERR);
	ft_putstr_fd(location, STDERR);
	ft_putendl_fd(".", STDERR);
	reset_write_color(STDERR);
}

void	perror_quote(char *location)
{
	set_write_color(RED, STDERR);
	ft_putendl_fd("Error ... (ﾉ･д･)ﾉ", STDERR);
	ft_putendl_fd("An unclose quote has been detected.", STDERR);
	ft_putstr_fd("See : ", STDERR);
	ft_putstr_fd(location, STDERR);
	ft_putendl_fd(".", STDERR);
	reset_write_color(STDERR);
}
