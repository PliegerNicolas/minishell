/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:24:12 by nplieger          #+#    #+#             */
/*   Updated: 2023/03/06 10:28:07 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	prompt(void)
{
	t_bool	previous_command_exit_status;
	char	*arg;

	previous_command_exit_status = 0;
	while (1)
	{
		if (prev_command_exit_status == 0)
			printf("%s→  %sminishell %s✗%s ", GREEN, CYAN, YELLOW, WHITE);
		else
			printf("%s→  %sminishell %s✗%s ", RED, CYAN, YELLOW, WHITE);
		arg = readline(0);
		free(arg);
	}
}

int	main(void)
{
	prompt();
	return (0);
}
