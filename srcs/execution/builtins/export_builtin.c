/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 15:14:22 by nicolas           #+#    #+#             */
/*   Updated: 2023/06/17 18:48:53 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static t_bool	verify_argument(char *s)
{
	size_t	i;

	if (!s)
		return (TRUE);
	i = 0;
	while (s[i] && s[i] != '=')
	{
		if ((s[i] >= 'a' && s[i] <= 'z')
			|| (s[i] >= 'A' && s[i] <= 'Z') || s[i] == '_')
			i++;
		else if (i != 0 && (s[i] >= '0' && s[i] <= '9'))
			i++;
		else
		{
			ft_putendl_fd("export: not a valid identifier", STDERR);
			return (g_status = general_failure, TRUE);
		}
	}
	return (FALSE);
}

static char	*get_var_name(char *s, size_t *i)
{
	char	*name;

	if (!s)
		return (NULL);
	while (s[*i] != '=')
		(*i)++;
	name = ft_substr(s, 0, *i);
	if (!name)
		return (perror_malloc("test"), NULL);
	(*i)++;
	return (name);
}

static char	**update_envp(char *str, const char *name, char **envp)
{
	size_t	i;

	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], name, ft_strlen(name)) != 0)
		i++;
	if (envp[i])
	{
		free(envp[i]);
		envp[i] = str;
	}
	else
	{
		envp = ft_append_to_string_array(envp, str);
		if (!envp)
			return (NULL);
	}
	return (envp);
}

static t_bool	export(char *s, char ***envp)
{
	char	*name;
	size_t	i;

	if (!s)
		return (g_status = general_failure, TRUE);
	if (!ft_strchr(s, '='))
		return (g_status = success, FALSE);
	i = 0;
	name = get_var_name(s, &i);
	if (!name)
		return (g_status = general_failure, TRUE);
	*envp = update_envp(s, name, *envp);
	if (!envp || !*envp)
		return (free(name), g_status = general_failure, TRUE);
	return (free(name), g_status = success, FALSE);
}

t_bool	export_builtin(t_lexer *lexer, char ***envp)
{
	char	*str;
	size_t	len;
	size_t	i;

	len = ft_strarrlen((const char **)lexer->args);
	if (len == 0)
		return (g_status = general_failure, FALSE);
	else if (len == 1)
		return (put_exported(*envp), g_status = success, FALSE);
	i = 1;
	while (lexer->args[i])
	{
		str = get_quoteless_str(lexer->args[i++]);
		if (verify_argument(str))
			return (free(str), g_status = general_failure, FALSE);
		if (export(str, envp))
			return (free(str), g_status = general_failure, TRUE);
	}
	return (FALSE);
}
