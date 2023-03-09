/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 23:12:52 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/09 17:48:53 by nicolas          ###   ########.fr       */
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
		rl_replace_line("", 0);
		rl_on_new_line();
		prompt_prefix();
	}
}
