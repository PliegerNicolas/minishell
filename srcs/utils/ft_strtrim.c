/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:09:33 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/06 11:09:40 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*str;
	size_t		i;
	size_t		left_offset;
	size_t		right_offset;

	if (!s1 || !set)
		return (NULL);
	left_offset = 0;
	right_offset = ft_strlen(s1);
	while (s1[left_offset] && ft_strchr(set, s1[left_offset]))
		left_offset++;
	if (left_offset == right_offset)
		return (ft_strdup(""));
	while (right_offset > left_offset && ft_strchr(set, s1[right_offset]))
		right_offset--;
	str = malloc((++right_offset - left_offset + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (left_offset < right_offset)
		str[i++] = s1[left_offset++];
	str[i] = '\0';
	return (str);
}
