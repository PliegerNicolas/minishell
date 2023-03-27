/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 19:46:27 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/28 01:48:21 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

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

static int	get_options_len(const char *quoteless_cmd)
{
	int	len;

	len = 0;
	if (quoteless_cmd[0] != '-')
		return (perror_invalid_options(), 0);
	while (quoteless_cmd[1 + len])
	{
		if (ft_isspace(quoteless_cmd[1 + len]))
			return (perror_invalid_options(), 0);
		else if (quoteless_cmd[1 + len] == '-')
			return (perror_invalid_options(), 0);
		else
			len++;
	}
	return (len);
}

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
