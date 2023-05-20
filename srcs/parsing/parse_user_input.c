/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_user_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 23:54:01 by nicolas           #+#    #+#             */
/*   Updated: 2023/05/20 17:01:32 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static t_bool	is_between_quotes(char c, enum e_quote_status *quote_status)
{
	if (!c)
		return (FALSE);
	if (*quote_status == none && c == '\'')
		*quote_status = single_quote;
	else if (*quote_status == none && c == '\"')
		*quote_status = double_quote;
	else if (*quote_status == single_quote && c == '\'')
		*quote_status = none;
	else if (*quote_status == double_quote && c == '\"')
		*quote_status = none;
	else if (*quote_status == none)
		return (FALSE);
	return (TRUE);
}

static char	*replace_backslashes(char *line)
{
	char				*substr;
	enum e_quote_status	quote_status;
	enum e_quote_status	mem_quote;
	size_t				i;

	if (!line)
		return (NULL);
	i = 0;
	quote_status = none;
	while (line[i])
	{
		mem_quote = quote_status;
		if (is_between_quotes(line[i], &quote_status) && quote_status != mem_quote)
			i++;
		else if (quote_status == single_quote || line[i] != '\\')
			i++;
		else if (line[i] == '\\' && line[i + 1] && (line[i + 1] == '\'' || line[i + 1] == '\"'))
			i++;
		else if (line[i] == '\\' && line[i + 1] && line[i + 1] != '\\'
			&& quote_status == double_quote)
		{
			substr = ft_substr(line + i, 0, 2);
			if (!substr)
				return (perror_malloc("test5"), free(line), NULL);
			if (ft_strncmp(line + i, "\\n", 2) == 0)
				line = replace_first(line, substr, "\n");
			else if (ft_strncmp(line + i, "\\t", 2) == 0)
				line = replace_first(line, substr, "\t");
			else if (ft_strncmp(line + i, "\\v", 2) == 0)
				line = replace_first(line, substr, "\v");
			else if (ft_strncmp(line + i, "\\f", 2) == 0)
				line = replace_first(line, substr, "\f");
			else if (ft_strncmp(line + i, "\\r", 2) == 0)
				line = replace_first(line, substr, "\r");
			else
			{
				line = replace_first(line, substr, substr + 1);
				if (!line)
					return (NULL);
			}
			i++;
		}
		else
		{
			substr = ft_substr(line + i, 0, 2);
			if (!substr)
				return (perror_malloc("test6"), free(line), NULL);
			line = replace_first(line, substr, substr + 1);
			if (!line)
				return (NULL);
			i++;
		}
	}
	return (line);
}

t_commands	*parse_user_input(char *line, char ***envp)
{
	t_commands	*commands;

	if (!line)
		return (NULL);
	if (quote_error(line, none))
		return (perror_quote(), free(line), NULL);
	line = substitute_line_content(line, 0, none, envp);
	if (!line)
		return (NULL);
	line = replace_backslashes(line);
	if (!line)
		return (NULL);
	/*
	if (line)
	{
		printf("%s\n", line);
		free(line);
		return (NULL);
	}
	*/
	if (!line)
		return (NULL);
	commands = generate_commands(line, envp);
	if (!commands)
		return (free(line), NULL);
	return (free(line), commands);
}
