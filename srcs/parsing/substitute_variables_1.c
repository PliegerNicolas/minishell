/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_variables_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 00:02:15 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/28 02:01:10 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/*
	This function goes through the line to find the next valid index.
	It looks for a '$' and ensures it's followed by other chars but quotes.
	A variable ends if quote is met, another '$' or a whitespace.

	It returns FALSE if a variable is found, else TRUE.
*/
static t_bool	scan_line(char *line, size_t *i,
	enum e_quote_status *quote_status)
{
	while (line[*i] && line[*i + 1])
	{
		if (set_quotestatus(line + *i, quote_status))
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

/*
	This function retrieves multiple values and stores it in a char **.

	var_landmarks[0] = what should be replaced by the variable's value
					   (ex : ${USER} or $USER).
	var_landmarks[1] = the variable's name. (ex : USER).
	var_landmarks[2] = the variable's value. (ex : nicolas).

	Returns var_landmarks or NULL on error.
*/
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

/*
	This function substitutes the substr by it's replacement value.

	@lens[0] = line's length.
	@lens[1] = substr's length.
	@lens[2] = replacement's length.

	It returns NULL on error or free's the given length and returns the new
	one.
*/
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

/*
	This function takes a line and substitutes it's contained variables
	according to the following format : $VARIABLE, ${VARIABLE}.
	It uses a recursive method. It also recognizes "$?" as a special case.
	
	- scan_line() : moves the cursor to find the next valid variable's index.
	- var_landmarks() : props a lot of variables in a char ** for ease of use.
						It should contain for example the part of the string
						that should get replaced, the variable's name and it's
						value.
	- substitute_variable() : replaces the variable by it's value.

	Returns the given line with subsituted variables.
*/
char	*substitute_line_content(char *line, size_t i,
	enum e_quote_status quote_status)
{
	char	**var_landmarks;

	if (!line || !line[i] || scan_line(line, &i, &quote_status))
		return (line);
	var_landmarks = get_var_landmarks(line, i);
	if (!var_landmarks)
		return (free(line), NULL);
	line = substitute_variable(line, var_landmarks[0], var_landmarks[2]);
	free_str_arr(var_landmarks);
	return (substitute_line_content(line, i, quote_status));
}
