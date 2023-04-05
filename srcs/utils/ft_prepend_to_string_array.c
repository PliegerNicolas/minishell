/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prepend_to_string_array.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:53:07 by nicolas           #+#    #+#             */
/*   Updated: 2023/04/05 14:09:26 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void	free_array(char **str_arr)
{
	size_t	i;

	if (!str_arr)
		return ;
	i = 0;
	while (str_arr[i])
		free(str_arr[i++]);
	free(str_arr);
}

char	**ft_prepend_to_string_array(char **str_arr, char *str)
{
	char	**new_str_arr;
	size_t	len;
	size_t	i;

	if (!str_arr)
		return (NULL);
	len = 0;
	while (str_arr[len])
		len++;
	new_str_arr = malloc((len + 2) * sizeof(*new_str_arr));
	if (!new_str_arr)
		return (perror_malloc("@new_str_arr (srcs/utils/ft_append_to_string_arr\
ay.c #ft_append_to_string_array)"), free_array(str_arr), NULL);
	i = 0;
	new_str_arr[i++] = str;
	while (i < len)
	{
		new_str_arr[i] = str_arr[i];
		i++;
	}
	new_str_arr[i] = 0;
	free(str_arr);
	return (new_str_arr);
}
