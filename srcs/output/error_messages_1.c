/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 11:30:19 by nicolas           #+#    #+#             */
/*   Updated: 2023/04/05 03:47:38 by nicolas          ###   ########.fr       */
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

void	perror_environnement(void)
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

void	perror_bad_substitution(void)
{
	set_write_color(RED, STDERR);
	ft_putendl_fd("Error ... ＼(;ﾟ∇ﾟ)/", STDERR);
	ft_putendl_fd("Bad substitution.", STDERR);
	reset_write_color(STDERR);
}

void	perror_quote(void)
{
	set_write_color(RED, STDERR);
	ft_putendl_fd("Error ... ಠ‿ಠ", STDERR);
	ft_putendl_fd("Open quote.", STDERR);
	reset_write_color(STDERR);
}
