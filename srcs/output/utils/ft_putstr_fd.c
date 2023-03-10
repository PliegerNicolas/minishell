/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:12:43 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/07 23:06:55 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_putstr_fd(char *s, int fd)
{
	int		i;

	i = 0;
	if (s)
		while (*s)
			i += write(fd, s++, 1);
	return (i);
}