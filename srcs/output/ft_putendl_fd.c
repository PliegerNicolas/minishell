/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:11:09 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/07 23:07:04 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_putendl_fd(char *s, int fd)
{
	int		i;

	i = 0;
	if (!s)
		return (i);
	i += ft_putstr_fd(s, fd);
	return (i + ft_putchar_fd('\n', fd));
}
