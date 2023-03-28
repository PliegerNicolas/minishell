/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arguments.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 19:46:39 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/28 02:46:53 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static t_bool	new_str_arr(const char **cmds, char ***args)
{
	char	**new_str_arr;
	size_t	len;

	if (!cmds)
		return (FALSE);
	len = 0;
	while (cmds[len])
		len++;
	if (!len)
		return (*args = NULL, FALSE);
	new_str_arr = ft_calloc((len + 1), sizeof(*new_str_arr));
	if (!new_str_arr)
		return (perror_malloc("@new_str_arr (srcs/parsing/get_arguments.c #new_\
str_arr"), TRUE);
	return (*args = new_str_arr, FALSE);
}

t_bool	get_arguments(const char **cmds, char ***arguments)
{
	size_t	i;

	if (!cmds)
		return (FALSE);
	else if (arguments && *arguments)
		return (FALSE);
	if (!new_str_arr(cmds, arguments))
		return (FALSE);
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
