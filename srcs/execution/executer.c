/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 00:02:51 by nicolas           #+#    #+#             */
/*   Updated: 2023/04/16 17:49:27 by nicolas          ###   ########.fr       */
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

	if (!commands)
		return ;
	i = 1;
	printf("%s===== ===== ===== ===== =====%s\n", YELLOW, WHITE);
	while (commands)
	{
		printf("%s=== Command nº%ld ===%s\n", PURPLE, i++, WHITE);
		printf("commands->cmd : %s\n", commands->cmd);
		lexer = commands->lexer;
		while (lexer)
		{
			printf("%s< Lexer nº%ld >%s\n", CYAN, lexer->id, WHITE);
			if (lexer->cmd)
				printf("lexer->cmd : %s\n", lexer->cmd);
			else
				printf("lexer->cmd : NULL\n");
			if (lexer->exec)
				printf("lexer->exec : %s\n", lexer->exec);
			else
				printf("lexer->exec : NULL\n");
			if (lexer->options)
			{
				j = 0;
				while (lexer->options[j])
				{
					printf("lexer->options[%ld] : %s\n", j, lexer->options[j]);
					j++;
				}
			}
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
			printf("lexer->redir_path[0] : %s\n", lexer->redir_path[0]);
			printf("lexer->redir_path[1] : %s\n", lexer->redir_path[1]);
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

/*
void	close_fds(int *pipefds, int *previous_fd)
{
	if (pipefds[0] != -1)
		close(pipefds[0]);
	if (pipefds[1] != -1)
		close(pipefds[1]);
	if (*previous_fd != -1)
	{
		close(*previous_fd);
		*previous_fd = -1;
	}
}
*/

static t_bool	lexer_execution(t_lexer *lexer, char ***envp)
{
	int	prev_fd;

	if (!lexer)
		return (FALSE);
	prev_fd = -1;
	while (lexer)
	{
		if (is_builtin(lexer->exec))
		{
			if (builtin_execution(lexer, &prev_fd, envp))
				return (TRUE);
		}
		else
			if (external_execution(lexer, &prev_fd, envp))
				return (TRUE);
		if (!lexer->next && prev_fd != -1)
		{
			put_fd(prev_fd);
			close(prev_fd);
		}
		lexer = lexer->next;
	}
	return (FALSE);
}

static t_bool	commands_execution(t_commands *commands, char ***envp)
{
	t_commands	*current_command;

	if (!commands)
		return (FALSE);
	current_command = commands;
	while (current_command && current_command->lexer)
	{
		if (lexer_execution(current_command->lexer, envp))
			return (TRUE);
		current_command = current_command->next;
	}
	return (FALSE);
}

enum e_status	executer(char ***envp, char *line)
{
	t_commands	*commands;

	if (!line || !*envp)
		return (free(line), general_failure);
	if (!*line)
		return (free(line), success);
	commands = parse_user_input(line, envp);
	if (!commands)
		return (general_failure);
	//put_commands(commands);
	if (commands_execution(commands, envp))
		return (free_commands(commands), g_status);
	unlink(".heredoc");
	return (free_commands(commands), success);
}
