/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 23:49:38 by nicolas           #+#    #+#             */
/*   Updated: 2023/05/08 15:09:30 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void	clear_and_exit(t_commands *commands, char ***envp, int *exit_status)
{
	free_commands(commands);
	free_envp(*envp);
	close_stds();
	if (exit_status)
		exit(*exit_status);
	else
		exit((int)g_status);
}

static int	is_num(const char *s)
{
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (FALSE);
		s++;
	}
	return (TRUE);
}

t_bool	exit_builtin(t_commands *commands, t_lexer *lexer, char ***envp)
{
	size_t			len;
	long long int	exit_status;

	ft_putendl_fd("exit", STDOUT);
	len = ft_strarrlen((const char **)lexer->args);
	if (len > 1)
	{
		exit_status = ft_atolli(lexer->args[1]);
		if (!is_num(lexer->args[1])
			|| exit_status < MIN_INT || exit_status > MAX_INT)
		{
			errno = EINVAL;
			perror("exit");
			g_status = misuse_of_shell_builtins;
		}
		else if (len > 2)
		{
			errno = E2BIG;
			return (perror("exit"), g_status = misuse_of_shell_builtins, FALSE);
		}
		else
			clear_and_exit(commands, envp, (int *)&exit_status);
	}
	clear_and_exit(commands, envp, NULL);
	return (g_status = success, FALSE);
}
