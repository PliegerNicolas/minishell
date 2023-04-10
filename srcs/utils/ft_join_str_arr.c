/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_str_arr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 01:26:30 by nicolas           #+#    #+#             */
/*   Updated: 2023/04/10 02:17:37 by nicolas          ###   ########.fr       */
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

static int	arr_len(char **arr)
{
	int	i;

	if (!arr)
		return (0);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}

char	**ft_join_str_arr(char **arr1, char **arr2)
{
	char	**new_arr;
	size_t	i;
	size_t	j;

	if (!arr1 && !arr2)
		return (NULL);
	new_arr = malloc((arr_len(arr1) + arr_len(arr2) + 1) * sizeof(*new_arr));
	if (!new_arr)
		return (NULL);
	i = 0;
	while (arr1[i])
	{
		new_arr[i] = ft_strdup(arr1[i]);
		if (!new_arr[i++])
			return (perror_malloc("@new_arr (srcs/utils/ft_join_str_arr.c #ft_j\
oin_str_arr)"), free_array(new_arr), NULL);
	}
	j = 0;
	while (arr2[j])
	{
		new_arr[i + j] = ft_strdup(arr2[j]);
		if (!new_arr[j++])
			return (perror_malloc("@new_arr (srcs/utils/ft_join_str_arr.c #ft_j\
oin_str_arr)"), free_array(new_arr), NULL);
	}
	new_arr[i + j] = NULL;
	return (new_arr);
}
