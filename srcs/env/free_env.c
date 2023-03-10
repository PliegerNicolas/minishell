/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 18:29:09 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/08 18:30:20 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/*
	Frees safely envp (environnement pointer).
*/
void	free_envp(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
		free(envp[i++]);
	if (envp)
		free(envp);
}
