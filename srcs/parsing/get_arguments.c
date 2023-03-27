/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arguments.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 19:46:39 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/28 01:43:03 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static char	**new_str_arr(const char **cmds)
{
	char	**new_str_arr;
	size_t	len;

	if (!cmds)
		return (NULL);
	len = 0;
	while (cmds[len])
		len++;
	new_str_arr = ft_calloc((len + 1), sizeof(*new_str_arr));
	if (!new_str_arr)
		return (perror_malloc("@new_str_arr (srcs/parsing/get_arguments.c #new_\
str_arr"), NULL);
	return (new_str_arr);
}

t_bool	get_arguments(const char **cmds, char ***arguments)
{
	size_t	i;

	if (!cmds)
		return (FALSE);
	else if (arguments && *arguments)
		return (FALSE);
	*arguments = new_str_arr(cmds);
	if (!*arguments)
		return (*arguments = NULL, TRUE);
	i = 0;
	while (cmds[i])
	{
		(*arguments)[i] = ft_strdup(cmds[i]);
		if (!*arguments)
			return (perror_malloc("@*arguments (srcs/parsing/get_arguments.c #g\
et_arguments"), free_str_arr(*arguments), TRUE);
		(*arguments)[i] = remove_quotes((*arguments)[i], none);
		if (!*arguments)
			return (perror_malloc("@*arguments (srcs/parsing/get_arguments.c #g\
et_arguments"), free_str_arr(*arguments), TRUE);
		i++;
	}
	return (FALSE);
}
