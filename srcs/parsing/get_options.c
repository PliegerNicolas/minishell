/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 19:46:27 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/26 15:12:47 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static char	*malloc_options(const char *cmd)
{
	char	*options;
	size_t	i;
	size_t	len;

	if (!cmd)
		return (NULL);
	i = 0;
	len = 0;
	while (cmd[i + len] && ft_isnextcharset(cmd + i + len, "-"))
	{
		while (cmd[i + len] != '-')
			i++;
		if (cmd[i + len])
			i++;
		while (cmd[i + len] && !ft_isspace(cmd[i + len]))
			len++;
	}
	options = malloc((len + 1) * sizeof(*options));
	if (!options)
		return (perror_malloc("@options (srcs/parsing/get_options.c #malloc_opt\
ions)"), NULL);
	return (options);
}

t_bool	get_options(const char *cmd, size_t *i, char **options)
{
	size_t	len;

	if (!cmd || !options)
		return (*options = NULL, FALSE);
	else if (options && *options)
		return (free(*options), TRUE);
	while (cmd[*i] && ft_isspace(cmd[*i]))
		(*i)++;
	if (cmd[*i] != '-')
		return (*options = NULL, FALSE);
	*options = malloc_options(cmd + *i);
	if (!*options)
		return (TRUE);
	len = 0;
	while (cmd[*i] && ft_isnextcharset(cmd + *i, "-"))
	{
		while (cmd[*i] != '-')
			(*i)++;
		if (cmd[*i])
			(*i)++;
		while (cmd[*i] && !ft_isspace(cmd[*i]))
			(*options)[len++] = cmd[(*i)++];
	}
	(*options)[len] = '\0';
	return (FALSE);
}
