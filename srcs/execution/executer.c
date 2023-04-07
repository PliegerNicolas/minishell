/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 00:02:51 by nicolas           #+#    #+#             */
/*   Updated: 2023/04/08 01:21:23 by nicolas          ###   ########.fr       */
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

/*
static char	*get_input_str(t_lexer *lexer, char *filename)
{
	char			*input_str;
	struct stat		st;
	int				fd;
	ssize_t			bytes_read;

	if (!lexer || !filename || lexer->redir_type[0] == no_redir)
		return (NULL);
	if (access(filename, F_OK) == -1)
		return (perror_no_such_file_or_dir(filename), NULL);
	if (stat(filename, &st) == -1)
		return (perror_file(), NULL);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (perror_file(), NULL);
	input_str = malloc(((off_t)st.st_size + 1) * sizeof(*input_str));
	if (!input_str)
		return (perror_malloc("@input_str (srcs/execution/executer.c #get_input\
_str)"), close(fd), NULL);
	bytes_read = read(fd, input_str, (off_t)st.st_size);
	input_str[bytes_read] = '\0';
	return (close(fd), input_str);
}

static t_bool	linear_command_execution(t_commands	*commands, char	***envp)
{
	t_lexer	*lexer;
	char	*input_str;
	char	*output_str;

	if (!commands)
		return (FALSE);
	while (commands)
	{
		lexer = commands->lexer;
		while (lexer)
		{
			input_str = get_input_str(lexer, lexer->redir_path[0]);
			if (input_str)
			{
				printf("%s\n", input_str);
				free(input_str);
			}
			lexer = lexer->next;
		}
		commands = commands->next;
	}
	(void)envp;
	return (FALSE);
}
*/

// Si redirect > ou >>, mise en fichier de sortie.
// Si redirect < ou <<, ne pas transmettre.
// Si next pas de redirection < ou << et actuel pas de redirect > ou >>, transmission
static t_bool	linear_command_execution(t_commands *commands, char ***envp)
{
	t_commands	*current_command;
	t_lexer		*current_lexer;
	pid_t		pid;
	int			pipefds[2];

	if (!commands)
		return (FALSE);
	current_command = commands;
	while (current_command)
	{
		current_lexer = current_command->lexer;
		while (current_lexer)
		{
			if (current_lexer->next && pipe(pipefds) == -1)
				return (TRUE); // pipe error or stop
			pid = fork();
			if (pid == -1)
				return (TRUE); // fork error
			else if (pid == 0)
			{
				if (current_lexer->next)
				{
					dup2(pipefds[1], STDOUT_FILENO);
					close(pipefds[0]);
				}
				if (current_lexer != commands->lexer)
				{
					dup2(pipefds[0], STDIN_FILENO);
					close(pipefds[1]);
				}
				if (execve(current_lexer->exec, current_lexer->args, *envp) == -1)
				{
					perror("execve");
					return (free_commands(commands), TRUE);
				}
				return (free_commands(commands), TRUE);
			}
			if (current_lexer != commands->lexer)
				close(pipefds[0]);
			if (current_lexer->next)
				close(pipefds[1]);
			current_lexer = current_lexer->next;
		}
		waitpid(pid, NULL, 0);
		current_command = current_command->next;
	}
	(void)envp;
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
	if (linear_command_execution(commands, envp))
		return (free_commands(commands), g_status);
	return (free_commands(commands), success);
}
