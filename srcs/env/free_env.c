/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 18:29:09 by nicolas           #+#    #+#             */
/*   Updated: 2023/05/09 22:23:58 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/*
	Frees safely envp (environnement pointer).
*/
void	free_envp(char **envp)
{
	int		i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
		free(envp[i++]);
	if (envp)
		free(envp);
}
