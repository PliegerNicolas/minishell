/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 22:04:31 by nicolas           #+#    #+#             */
/*   Updated: 2023/06/16 22:12:26 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*filter_out_redirection(char *s)
{
	char				*str1;
	char				*str2;
	size_t				i;
	enum e_quote_status	q_status;

	i = 0;
	q_status = none;
	while (s[i])
	{
		is_between_quotes(s[i], &q_status);
		if (q_status == none && (s[i] == '<' || s[i] == '>'))
			break ;
		i++;
	}
	str1 = ft_substr(s, 0, i);
	if (!str1)
		return (NULL);
	str2 = get_quoteless_str(str1);
	free(str1);
	if (!str2)
		return (NULL);
	return (str2);
}
