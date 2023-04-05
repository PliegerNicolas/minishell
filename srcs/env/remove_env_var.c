/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:01:10 by nicolas           #+#    #+#             */
/*   Updated: 2023/04/05 14:47:40 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	**remove_env_var(char *var_name, char **envp)
{
	char	**new_envp;
	size_t	i;
	size_t	j;

	if (!envp)
		return (NULL);
	new_envp = malloc(env_len(envp) * sizeof(*new_envp));
	if (!new_envp)
		return (perror_malloc("@new_envp (srcs/env/remove_env_var.c #remove_env\
_var)"), free_envp(envp), NULL);
	i = 0;
	j = 0;
	while (envp[i] && ft_strncmp(var_name, envp[i], ft_strlen(var_name) != 0))
		new_envp[i++] = envp[j++];
	j++;
	while (envp[i])
		new_envp[i++] = envp[j++];
	new_envp[i] = 0;
	return (new_envp);
}
