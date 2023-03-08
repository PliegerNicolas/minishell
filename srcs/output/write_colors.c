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

void	set_write_color(char *s, int fd)
{
	ft_putstr_fd(s, fd);
}

void	reset_write_color(int fd)
{
	ft_putstr_fd("\033[0m", fd);
}
