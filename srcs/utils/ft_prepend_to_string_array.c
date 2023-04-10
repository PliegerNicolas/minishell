/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prepend_to_string_array.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:53:07 by nicolas           #+#    #+#             */
/*   Updated: 2023/04/10 02:15:15 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static size_t	arr_len(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

char	**ft_prepend_to_string_array(char **str_arr, char *str)
{
	char	**new_arr;
	size_t	len;
	size_t	i;

	if (!str_arr || !str)
		return (NULL);
	len = arr_len(str_arr);
	new_arr = malloc((len + 2) * sizeof(*new_arr));
	if (!new_arr)
		return (perror_malloc("@new_arr (srcs/utils/ft_append_to_string_array.c\
#ft_append_to_string_array)"), NULL);
	i = 0;
	new_arr[i] = str;
	while (i < len)
	{
		new_arr[i + 1] = str_arr[i];
		i++;
	}
	new_arr[len + 1] = NULL;
	free(str_arr);
	return (new_arr);
}
