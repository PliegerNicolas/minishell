/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_variables_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 00:02:15 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/22 22:56:26 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static t_bool	scan_line(char *line, size_t *i,
	enum e_quote_status *quote_status)
{
	while (line[*i] && line[*i + 1])
	{
		if (set_quotestatus(line[*i], quote_status))
			(*i)++;
		else if (*quote_status == single_quote)
			(*i)++;
		else
		{
			if (line[*i] == '$' && line[*i + 1] == '$')
				(*i)++;
			else if (line[*i] == '$' && (line[*i + 1] == '\''
					|| line[*i + 1] == '\"'))
				(*i)++;
			else if (line[*i] == '$' && !ft_isspace(line[*i + 1]))
				return (FALSE);
			else
				(*i)++;
		}
	}
	return (TRUE);
}

static char	**get_var_landmarks(char *line, size_t i)
{
	char	**var_landmarks;
	size_t	len;
	t_bool	brackets;

	if (!line && !*line)
		return (NULL);
	if (line[i] && !ft_followed_chars(line + i, '{', '}'))
		return (perror_bad_substitution(), NULL);
	brackets = FALSE;
	if (line[i + 1] && line[i + 1] == '{')
		brackets = TRUE;
	len = get_placeholder_len(line, i, brackets);
	var_landmarks = set_var_landmarks(line, i, ++len, brackets);
	if (!var_landmarks)
		return (NULL);
	return (var_landmarks);
}

static char	*substitute_variable(char *line, const char *substr,
	const char *replacement)
{
	char	*new_line;
	char	*pos;
	size_t	lens[3];

	if (!line || !substr || !replacement)
		return (line);
	lens[0] = ft_strlen(line);
	pos = ft_strnstr(line, substr, lens[0]);
	lens[1] = ft_strlen(substr);
	lens[2] = ft_strlen(replacement);
	new_line = malloc((lens[0] + lens[2] - lens[1] + 1) * sizeof(*new_line));
	if (!new_line)
	{
		perror_malloc("@variable_name (srcs/parsing/substitute_variables.c #sub\
stitute_variables)");
		return (free(line), NULL);
	}
	ft_memcpy(new_line, line, pos - line);
	ft_memcpy(new_line + (pos - line), replacement, lens[2]);
	ft_memcpy(new_line + (pos - line) + lens[2], pos + lens[1],
		line + lens[0] - (pos + lens[1]));
	new_line[lens[0] + (lens[2] - lens[1])] = '\0';
	return (free(line), new_line);
}

char	*remove_quotes(char *line, enum e_quote_status quote_status)
{
	char				*new_line;
	size_t				i;
	size_t				len;

	i = 0;
	len = 0;
	while (line[i])
		if (!set_quotestatus(line[i++], &quote_status))
			len++;
	new_line = malloc((len + 1) * sizeof(*new_line));
	if (!new_line)
		return (free(line), perror_malloc("@new_line (srcs/parsing/substitute_v\
ariables.c #remove_quotes)"), NULL);
	i = 0;
	len = 0;
	while (line[i])
	{
		if (!set_quotestatus(line[i], &quote_status))
			new_line[len++] = line[i];
		i++;
	}
	new_line[len] = '\0';
	return (free(line), new_line);
}

char	*substitute_line_content(char *line, size_t i,
	enum e_quote_status quote_status)
{
	char	**var_landmarks;

	if (!line || !line[i] || scan_line(line, &i, &quote_status))
		return (remove_quotes(line, none));
	var_landmarks = get_var_landmarks(line, i);
	if (!var_landmarks)
		return (free(line), NULL);
	line = substitute_variable(line, var_landmarks[0], var_landmarks[2]);
	free_str_arr(var_landmarks);
	return (substitute_line_content(line, i, quote_status));
}
