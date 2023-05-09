/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 15:14:22 by nicolas           #+#    #+#             */
/*   Updated: 2023/05/09 23:30:12 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void	put_exported(char **envp)
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

static char	*find_name(const char *quoteless_str)
{
	char	*name;
	size_t	i;

	if (!quoteless_str)
		return (NULL);
	i = 0;
	while (quoteless_str[i] && quoteless_str[i] != '=')
		i++;
	name = ft_substr(quoteless_str, 0, i);
	if (!name)
		return (perror_malloc("@name (srcs/execuion/builtins/export_builtin.c #\
find_name"), NULL);
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

static t_bool	export(const char *s, char ***envp)
{
	char	*quoteless_str;
	char	*name;

	if (!s || !ft_strchr(s, '='))
		return (FALSE);
	quoteless_str = get_quoteless_str(s);
	if (!quoteless_str)
		return (g_status = general_failure, TRUE);
	name = find_name(quoteless_str);
	if (!name)
		return (free(quoteless_str), g_status = general_failure, TRUE);
	*envp = update_envp(quoteless_str, name, *envp);
	if (!envp || !*envp)
		return (free(name), g_status = general_failure, TRUE);
	return (free(name), FALSE);
}

t_bool	export_builtin(t_lexer *lexer, char ***envp)
{
	size_t	len;

	if (!lexer)
		return (FALSE);
	if (!envp || !*envp)
		return (g_status = general_failure, TRUE);
	len = ft_strarrlen((const char **)lexer->args);
	if (len > 2)
	{
		errno = E2BIG;
		return (perror("exit"), g_status = misuse_of_shell_builtins, FALSE);
	}
	else if (len == 2)
	{
		if (export(lexer->args[1], envp))
			return (g_status = general_failure, TRUE);
	}
	else if (len == 1)
		put_exported(*envp);
	return (g_status = success, FALSE);
}
