/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 23:12:52 by nicolas           #+#    #+#             */
/*   Updated: 2023/05/11 13:54:22 by nicolas          ###   ########.fr       */
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
void	sigint_handler(int signo)
{
	if (signo != SIGINT)
		return ;
	ft_putchar_fd('\n', STDIN);
	rl_replace_line("", STDIN);
	rl_on_new_line();
	g_status = termination_by_ctrl_c;
	ft_putstr_fd(RED, STDOUT);
	rl_redisplay();
	signal(SIGINT, sigint_handler);
}

void	proc_sigint_handler(int signo)
{
	if (signo != SIGINT)
		return ;
	ft_putendl_fd("^C", STDOUT);
	signal(SIGINT, proc_sigint_handler);
}

/*
	Tells the program to run sigint_handler on SIGINT (ctrl + c).
	Tells the program to ignorer the SIGQUIT signal (ctrl + \).
*/
void	setup_signals(void (*sig_handler)(int))
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

/*
	Resets all modifications done by setup_signals() to default behavior;
*/
void	reset_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
}
