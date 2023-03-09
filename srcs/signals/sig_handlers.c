/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 23:12:52 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/09 19:25:36 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void	sigint_handler(int signo)
{
	if (signo != SIGINT)
		return ;
	g_status = failure;
	ft_putchar_fd('\n', STDIN);
	rl_replace_line("", STDIN);
	rl_on_new_line();
	prompt_prefix();
	rl_redisplay();
}

void	setup_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
