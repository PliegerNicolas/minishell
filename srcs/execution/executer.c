/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 00:02:51 by nicolas           #+#    #+#             */
/*   Updated: 2023/04/04 18:36:42 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

// temp function for testing.
/*
static void	put_commands(t_commands *commands)
{
	t_lexer	*lexer;
	size_t	i;
	size_t	j;
	size_t	k;

	if (!commands)
		return ;
	i = 1;
	printf("%s===== ===== ===== ===== =====%s\n", YELLOW, WHITE);
	while (commands)
	{
		printf("%s=== Command nº%ld ===%s\n", PURPLE, i++, WHITE);
		printf("commands->cmd : %s\n", commands->cmd);
		lexer = commands->lexer;
		k = 0;
		while (lexer)
		{
			printf("%s< Lexer nº%ld >%s\n", CYAN, k++, WHITE);
			if (lexer->cmd)
				printf("lexer->cmd : %s\n", lexer->cmd);
			else
				printf("lexer->cmd : NULL\n");
			if (lexer->exec)
				printf("lexer->exec : %s\n", lexer->exec);
			else
				printf("lexer->exec : NULL\n");
			if (lexer->options)
				printf("lexer->options : %s\n", lexer->options);
			else
				printf("lexer->options : NULL\n");
			if (lexer->args)
			{
				j = 0;
				while (lexer->args[j])
				{
					printf("lexer->args[%ld] : %s\n", j, lexer->args[j]);
					j++;
				}
			}
			else
				printf("lexer->args : NULL\n");
			printf("lexer->pipefds[0] : %d\n", lexer->pipefds[0]);
			printf("lexer->pipefds[1] : %d\n", lexer->pipefds[1]);
			lexer = lexer->next;
			printf("%s< End lexer >%s\n", CYAN, WHITE);
		 }
		commands = commands->next;
		printf("%s=== === ==== === ===%s\n", PURPLE, WHITE);
		if (commands)
			printf("\n");
	}
	printf("%s===== ===== ===== ===== =====%s\n", YELLOW, WHITE);
}
*/

static t_bool	linear_command_execution(t_commands	*commands, char	**envp)
{
	t_lexer	*lexer;

	if (!commands || !envp)
		return (FALSE);
	while (commands)
	{
		lexer = commands->lexer;
		while (lexer)
		{
			if (execute_builtin(lexer, envp))
				return (TRUE);
			else if (execute_other(lexer, envp))
				return (TRUE);
			lexer = lexer->next;
		}
		commands = commands->next;
	}
	return (FALSE);
}

enum e_status	executer(char **envp, char *line)
{
	t_commands	*commands;

	if (!line || !envp)
		return (free(line), general_failure);
	if (!*line)
		return (free(line), success);
	commands = parse_user_input(line);
	if (!commands)
		return (general_failure);
	//put_commands(commands);
	if (linear_command_execution(commands, envp))
		return (free_commands(commands), g_status);
	return (free_commands(commands), success);
}
