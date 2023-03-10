/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:10:45 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/07 23:06:37 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/*
	Writes a character in terminal via the write function (unistd).
	It returns the number of written characters (1 systematically).
*/
int	ft_putchar_fd(char c, int fd)
{
	return (write(fd, &c, 1));
}
