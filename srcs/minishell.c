/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:24:12 by nplieger          #+#    #+#             */
/*   Updated: 2023/03/07 22:37:22 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	**g_envp;

/*
void	prompt(void)
{
	char	*arg;

	while (1)
	{
		printf("%s→  %sminishell %s✗%s ", CYAN, CYAN, YELLOW, WHITE);
		arg = readline(0);
		free(arg);
		break ;
	}
	rl_clear_history();
}
*/

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	if (initialize_env(env))
		return (1);
	put_env();
	//prompt();
	free_g_envp();
	return (0);
}
