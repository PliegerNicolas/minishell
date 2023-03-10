/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:34:03 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/07 23:07:38 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/*
	Puts a simple string. This function is used with the different color macros
	present in minishell.h ("RED", "GREEN", "CYAN", ...).
	This function exists for readability.
*/
int	set_write_color(char *s, int fd)
{
	return (ft_putstr_fd(s, fd));
}

/*
	Puts a simple string representing the default terminal color (white).
	This function exists for readability.
*/
int	reset_write_color(int fd)
{
	return (ft_putstr_fd("\033[0m", fd));
}
