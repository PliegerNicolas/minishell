/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:04:44 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/06 11:04:50 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*ft_strdup(const char *s)
{
	char		*ret;
	size_t		len;

	len = ft_strlen(s) + 1;
	ret = malloc(len * sizeof(char));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, s, len);
	return (ret);
}
