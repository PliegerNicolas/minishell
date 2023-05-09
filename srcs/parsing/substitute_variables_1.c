/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_variables_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 00:02:15 by nicolas           #+#    #+#             */
/*   Updated: 2023/05/09 18:58:38 by nicolas          ###   ########.fr       */
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
static char	**get_var_landmarks(char *line, size_t i, char ***envp)
{
	char	**var_landmarks;
	t_bool	brackets;

	if (!line && !*line)
		return (NULL);
	if (line[i] && !ft_followed_chars(line + i, '{', '}'))
		return (perror_bad_substitution(), NULL);
	brackets = FALSE;
	if (line[i + 1] && line[i + 1] == '{')
		brackets = TRUE;
	var_landmarks = set_var_landmarks(line, i, brackets, envp);
	if (!var_landmarks)
		return (NULL);
	return (var_landmarks);
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
	enum e_quote_status quote_status, char ***envp)
{
	char	**var_landmarks;

	if (!line || !line[i] || scan_line(line, &i, &quote_status))
		return (line);
	var_landmarks = get_var_landmarks(line, i, envp);
	if (!var_landmarks)
		return (free(line), NULL);
	line = replace_first(line, var_landmarks[0], var_landmarks[2]);
	free_str_arr(var_landmarks);
	return (substitute_line_content(line, i, quote_status, envp));
}
