/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:24:12 by nplieger          #+#    #+#             */
/*   Updated: 2023/02/23 15:10:14 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	prompt(void)
{
	char	*arg;

	while (1)
	{
		printf("%s minishell $> %s", GREEN, WHITE);
		arg = readline(0);
		free(arg);
	}
}

int	main(void)
{
	prompt();
	return (0);
}
