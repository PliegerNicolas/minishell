/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 22:34:26 by nicolas           #+#    #+#             */
/*   Updated: 2023/06/16 23:47:11 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/*
	Writes what is contained in the envp pointer (environnement pointer).
	In other terms, it writes all saved environnement variables.
*/
void	put_env(char **envp)
{
	int		i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

/*
	Returns the number of variables (lines) contained
	in envp (environnement pointer).
*/
size_t	env_len(char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

void	put_exported(char **envp)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (envp[i])
	{
		ft_putstr_fd("declare -x ", STDOUT);
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			ft_putchar_fd(envp[i][j++], STDOUT);
		ft_putstr_fd("=\"", STDOUT);
		ft_putstr_fd(envp[i] + ++j, STDOUT);
		ft_putendl_fd("\"", STDOUT);
		i++;
	}
}
