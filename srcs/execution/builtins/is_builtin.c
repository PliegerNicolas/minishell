/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 22:19:12 by nicolas           #+#    #+#             */
/*   Updated: 2023/04/11 22:19:17 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_bool	is_builtin(const char *str)
{
	if (ft_strncmp(str, "echo", 5) == 0)
		return (TRUE);
	else if (ft_strncmp(str, "cd", 3) == 0)
		return (TRUE);
	else if (ft_strncmp(str, "pwd", 4) == 0)
		return (TRUE);
	else if (ft_strncmp(str, "export", 7) == 0)
		return (TRUE);
	else if (ft_strncmp(str, "unset", 6) == 0)
		return (TRUE);
	else if (ft_strncmp(str, "env", 4) == 0)
		return (TRUE);
	else if (ft_strncmp(str, "exit", 5) == 0)
		return (TRUE);
	return (FALSE);
}
