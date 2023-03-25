/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_lexer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:11:36 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/25 19:48:05 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_lexer	*populate_lexer(t_lexer *lexer, const char *cmd, size_t i)
{
	if (!lexer)
		return (NULL);
	printf("%s\n", cmd);
	(void)i;
	return (lexer);
}
/*
static char	*get_exec(const char *cmd, size_t *i)
{
	char	*exec;
	size_t	start;
	size_t	len;

	if (!cmd)
		return (NULL);
	while (cmd[*i] && ft_isspace(cmd[*i]))
		(*i)++;
	start = *i;
	len = 0;
	while (cmd[*i + len] && !ft_isspace(cmd[*i + len]))
		len++;
	*i += len;
	exec = ft_substr(cmd, start, len);
	if (!exec)
		return (perror_malloc("@exec (srcs/parsing/populate_lexer.c #get_exec)"\
), NULL);
	return (exec);
}

static char	*malloc_options_str(const char *cmd, size_t *i)
{
	char	*options;
	size_t	j;
	size_t	len;

	if (!cmd)
		return (NULL);
	j = 0;
	len = 0;
	while (cmd[*i + j + len] && ft_isnextcharset(cmd + *i + j + len, "-"))
	{
		while (cmd[*i + j + len] != '-')
			j++;
		j++;
		while (cmd[*i + j + len] && !ft_isspace(cmd[*i + j + len]))
			len++;
	}
	options = malloc((len + 1) * sizeof(*options));
	if (!options)
		return (perror_malloc("@options (srcs/parsing/populate_lexer.c #malloc_\
options_str)"), NULL);
	return (options);
}

static t_bool	get_options(const char *cmd, size_t *i, char **options)
{
	size_t	len;

	if (!cmd)
		return (FALSE);
	else if (options && *options)
		return (free(*options), TRUE);
	while (cmd[*i] && ft_isspace(cmd[*i]))
		(*i)++;
	*options = malloc_options_str(cmd, i);
	if (!*options)
		return (TRUE);
	len = 0;
	while (cmd[*i] && ft_isnextcharset(cmd + *i, "-"))
	{
		while (cmd[*i] != '-')
			(*i)++;
		(*i)++;
		while (cmd[*i] && !ft_isspace(cmd[*i]))
			(*options)[len++] = cmd[(*i)++];
	}
	(*options)[len] = '\0';
	if (!**options)
		return (free(*options), *options = NULL, FALSE);
	return (FALSE);
}

static t_bool	get_arguments(const char *cmd, size_t *i, char ***args)
{
	char	**split;

	if (!cmd)
		return (FALSE);
	else if (args && *args)
		return (free_str_arr(*args), TRUE);
	if ((cmd + *i) && !*(cmd + *i))
		return (*args = NULL, FALSE);
	split = ft_setsplit_quotesafe(cmd + *i, WHITE_SPACES, none);
	if (!split)
		return (*args = NULL, TRUE);
	*args = split;
	return (FALSE);
}
*/

	/*
	if (!lexer)
		return (NULL);
	if (ft_isnextcharset(cmd, "-"))
		return (perror_command_not_found(), free_lexer(lexer), NULL);
	lexer->exec = get_exec(cmd, &i);
	if (!lexer->exec)
		return (free_lexer(lexer), NULL);
	if (get_options(cmd, &i, &lexer->options))
		return (free_lexer(lexer), NULL);
	if (get_arguments(cmd, &i, &lexer->args))
		return (free_lexer(lexer), NULL);
	return (lexer);
	*/
