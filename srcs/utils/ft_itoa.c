/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 20:11:11 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/18 20:11:18 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static size_t	ft_count_digits(const int n)
{
	int			val;
	size_t		len;

	len = 0;
	val = n;
	if (val == 0)
		return (1);
	if (val < 0)
	{
		val *= -1;
		len++;
	}
	while (!(val < 1 && val > -1))
	{
		val /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*s;
	size_t			len;
	size_t			i;
	unsigned int	nb;

	len = ft_count_digits(n);
	s = malloc((len + 1) * sizeof(char));
	if (!s)
		return (NULL);
	i = 0;
	s[len] = '\0';
	if (n == 0)
		s[--len] = '0';
	nb = (unsigned int)n;
	if (n < 0)
	{
		nb *= -1;
		s[i++] = '-';
	}
	while (len > i)
	{
		s[--len] = (nb % 10) + '0';
		nb /= 10;
	}
	return (s);
}
