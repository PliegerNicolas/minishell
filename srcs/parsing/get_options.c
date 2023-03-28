/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 19:46:27 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/28 15:04:17 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/*
	It removes the quotes of the given string.
	Returns the newly formatted string or NULL on error.
*/
static char	*get_quoteless_cmd(const char *cmd)
{
	char	*quoteless_cmd;

	if (!cmd)
		return (NULL);
	quoteless_cmd = ft_strdup(cmd);
	if (!quoteless_cmd)
		return (perror_malloc("@quoteless_cmd (srcs/parsing/get_options.c #get_\
quoteless_cmd)"), NULL);
	quoteless_cmd = remove_quotes(quoteless_cmd, none);
	if (!quoteless_cmd)
		return (NULL);
	return (quoteless_cmd);
}

/*
	This function replaces the options string and joins it with the
	added_options string.
	On success, returns the STRING, else NULL.
*/
static char	*add_to_existing_options(char *options, char *added_options)
{
	char	*new_options;

	if (!added_options)
		return (options);
	if (!options)
		return (added_options);
	else
	{
		new_options = ft_strjoin(options, added_options);
		free(added_options);
		free(options);
		if (!new_options)
			return (perror_malloc("@new_options (srcs/parsing/get_options.c #ge\
t_options)"), NULL);
	}
	return (new_options);
}

/*
	This function returns the option's length (ex : -ab = 2). If there is
	an error, 0 is returned.
*/
static int	get_options_len(const char *quoteless_cmd)
{
	int	len;

	len = 0;
	if (quoteless_cmd[0] != '-')
		return (perror_invalid_options(), 0);
	while (quoteless_cmd[1 + len])
		if (!ft_isalpha(quoteless_cmd[1 + len++]))
			return (perror_invalid_options(), 0);
	return (len);
}

/*
	This function first removes the quotes of the given str.
	It then removes unwanted characters ('-') and verifies if
	the option format is respected. If not, an error is returned.
	It then replaces the *options string by it's new joined version.

	It returns FALSE on success and TRUE on error.
*/
t_bool	get_options(const char *cmd, char **options)
{
	char	*quoteless_cmd;
	char	*added_options;
	int		len;

	if (!cmd)
		return (FALSE);
	quoteless_cmd = get_quoteless_cmd(cmd);
	if (!quoteless_cmd)
		return (TRUE);
	len = get_options_len(quoteless_cmd);
	if (!len)
		return (free(quoteless_cmd), TRUE);
	added_options = ft_substr(quoteless_cmd, 1, len);
	free(quoteless_cmd);
	if (!added_options)
		return (perror_malloc("@added_options (srcs/parsing/get_options.c #get_\
options)"), TRUE);
	*options = add_to_existing_options(*options, added_options);
	if (!*options)
		return (TRUE);
	return (FALSE);
}
