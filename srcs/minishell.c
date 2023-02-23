/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:24:12 by nplieger          #+#    #+#             */
/*   Updated: 2023/02/23 15:16:30 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	prompt(void)
{
	char	*arg;

	while (1)
	{
		printf("%s→  %sminishell %s✗%s ", GREEN, CYAN, YELLOW, WHITE);
		arg = readline(0);
		free(arg);
	}
}

int	main(void)
{
	prompt();
	return (0);
}
