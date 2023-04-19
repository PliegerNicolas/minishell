/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:01:10 by nicolas           #+#    #+#             */
/*   Updated: 2023/04/19 18:42:22 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static t_bool	verify_if_var_exists(const char *var_name, const char **envp)
{
	char	*found_var;

	found_var = get_env_var(var_name, envp);
	if (!found_var)
		return (TRUE);
	return (free(found_var), FALSE);
}

char	**remove_env_var(char *var_name, char **envp)
{
	char	**new_envp;
	size_t	i;
	size_t	j;

	if (!envp)
		return (NULL);
	if (!var_name)
		return (free_envp(envp), NULL);
	if (verify_if_var_exists(var_name, (const char **)envp))
		return (envp);
	new_envp = malloc(env_len(envp) * sizeof(*new_envp));
	if (!new_envp)
		return (perror_malloc("@new_envp (srcs/env/remove_env_var.c #remove_env\
_var)"), free_envp(envp), NULL);
	i = 0;
	j = 0;
	while (envp[i] && ft_strncmp(var_name, envp[i], ft_strlen(var_name)) != 0)
		new_envp[i++] = envp[j++];
	free(envp[j++]);
	while (envp[j])
		new_envp[i++] = envp[j++];
	new_envp[i] = 0;
	return (free(envp), new_envp);
}
