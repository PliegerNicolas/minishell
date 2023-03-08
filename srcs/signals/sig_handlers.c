/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 23:12:52 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/08 23:40:22 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/*
	DEFAULTS :
	- CTRL + C : sigint
	- CTRL + D : EOF 
	- CTRL + \ : sigquit
*/
void	sighandler(int sig)
{
	if (sig == SIGINT)
	{
		g_status = failure;
		ft_putchar_fd('\n', 1);
	}
}
