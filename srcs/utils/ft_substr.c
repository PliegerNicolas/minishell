/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:02:55 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/06 11:03:02 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char			*ret;
	size_t			i;
	unsigned int	max_len;

	if (!s)
		return (NULL);
	max_len = (unsigned int)ft_strlen(s);
	if (start > (max_len + 1))
		return (ft_strdup(""));
	if (len > (max_len + 1) || (start + len) > (max_len + 1))
		len = max_len - start;
	ret = malloc((len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	while (len-- && s[start])
		ret[i++] = s[start++];
	ret[i] = '\0';
	return (ret);
}
