/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arguments.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 19:46:39 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/27 13:19:14 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_bool	get_arguments(const char *cmd, size_t *i, char ***arguments,
	enum e_quote_status *quote_status)
{
	(void)cmd;
	(void)i;
	(void)quote_status;
	*arguments = NULL;
	return (FALSE);
}
