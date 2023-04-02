/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 00:02:51 by nicolas           #+#    #+#             */
/*   Updated: 2023/04/02 17:17:20 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

// temp function for testing.
static void	put_commands(t_commands *commands)
{
	t_lexer	*lexer;
	size_t	i;
	size_t	j;

	if (!commands)
		return ;
	i = 1;
	while (commands)
	{
		printf("%s=== Command nº%ld ===%s\n", CYAN, i++, WHITE);
		printf("commands->cmd : %s\n", commands->cmd);
		lexer = commands->lexer;
		printf("%s[Lexer/%s\n", CYAN, WHITE);
		if (lexer->cmd)
			printf("lexer->cmd : %s\n", lexer->cmd);
		if (lexer->exec)
			printf("lexer->exec : %s\n", lexer->exec);
		if (lexer->options)
			printf("lexer->options : %s\n", lexer->options);
		printf("lexer->pipefds[0] : %d\n", lexer->pipefds[0]);
		printf("lexer->pipefds[1] : %d\n", lexer->pipefds[1]);
		if (lexer->args)
		{
			j = 0;
			while (lexer->args[j])
			{
				printf("lexer->args[%ld] : %s\n", j, lexer->args[j]);
				j++;
			}
		}
		printf("%s/Lexer]%s\n", CYAN, WHITE);
		commands = commands->next;
		printf("%s=== === ==== === ===%s\n\n", CYAN, WHITE);
	}
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
	// temp
	put_commands(commands);
	// temp
	return (free_commands(commands), success);
}
