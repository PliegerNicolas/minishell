/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 04:43:50 by nicolas           #+#    #+#             */
/*   Updated: 2023/04/23 18:24:51 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static char	*join_env(const char *str1, const char *str2, char separator)
{
	char	*new_str;
	size_t	len_1;
	size_t	len_2;

	len_1 = ft_strlen(str1);
	len_2 = ft_strlen(str2);
	new_str = malloc((len_1 + len_2 + 2) * sizeof(*new_str));
	if (!new_str)
		return (perror_malloc("@new_str (srcs/utils/set_env_var.c #join_env)"),
			NULL);
	ft_memcpy(new_str, str1, len_1);
	new_str[len_1] = separator;
	ft_memcpy(new_str + len_1 + 1, str2, len_2);
	new_str[len_1 + len_2 + 1] = '\0';
	return (new_str);
}

char	**set_env_var(char *name, char *value, char **envp)
{
	char	*new_env_data;
	size_t	i;

	if (!envp)
		return (NULL);
	i = 0;
	new_env_data = NULL;
	while (envp[i] && ft_strncmp(name, envp[i], ft_strlen(name) != 0))
		i++;
	new_env_data = join_env(name, value, '=');
	if (!new_env_data)
		return (free_envp(envp), NULL);
	if (envp[i])
	{
		free(envp[i]);
		envp[i] = new_env_data;
	}
	else
	{
		envp = ft_append_to_string_array(envp, new_env_data);
		if (!envp)
			return (free(new_env_data), NULL);
	}
	return (envp);
}
