/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 23:12:52 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/10 14:10:54 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/*
	- Prints '\n' to indicate end of line to readline().
	- It then uses readline's library functions to construct a new prompt
		and flush the readline buffer from what was written last.
	- ft_putstr_fd is here to change the color of the ➜ in front of the
		readline prompt message to RED.
*/
static void	sigint_handler(int signo)
{
	if (signo != SIGINT)
		return ;
	ft_putchar_fd('\n', STDIN);
	rl_replace_line("", STDIN);
	rl_on_new_line();
	ft_putstr_fd(RED, STDIN);
	rl_redisplay();
}

/*
	Tells the program to run sigint_handler on SIGINT (ctrl + c).
	Tells the program to ignorer the SIGQUIT signal (ctrl + \).
*/
void	setup_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
