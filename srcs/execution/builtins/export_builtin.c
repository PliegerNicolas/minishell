/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 15:14:22 by nicolas           #+#    #+#             */
/*   Updated: 2023/04/05 23:28:20 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static char	*get_quoteless_str(const char *str)
{
	char	*quoteless_str;

	if (!str)
		return (NULL);
	quoteless_str = ft_strdup(str);
	if (!quoteless_str)
		return (perror_malloc("@quoteless_str (srcs/parsing/set_options.c #get_\
quoteless_str)"), NULL);
	quoteless_str = remove_quotes(quoteless_str, none);
	if (!quoteless_str)
		return (NULL);
	return (quoteless_str);
}

static char	*get_var_name(const char *quoteless_arg)
{
	char	*var_name;
	size_t	i;

	if (!quoteless_arg)
		return (NULL);
	i = 0;
	while (quoteless_arg[i] != '=')
		i++;
	var_name = ft_substr(quoteless_arg, 0, i);
	if (!var_name)
		return (perror_malloc("@var_name (srcs/execution/builtins/export_builti\
n.c #get_var_name)"), NULL);
	return (var_name);
}

static char	**update_envp(char *quoteless_arg, char ***envp, size_t i)
{
	if (!envp)
		return (NULL);
	if (!quoteless_arg)
		return (*envp);
	if ((*envp)[i])
	{
		free((*envp)[i]);
		(*envp)[i] = quoteless_arg;
	}
	else
	{
		*envp = ft_append_to_string_array(*envp, quoteless_arg);
		if (!*envp)
			return (NULL);
	}
	return (*envp);
}

t_bool	export(char *arg, char ***envp)
{
	char	*quoteless_arg;
	char	*var_name;
	size_t	i;

	if (!arg || !ft_strchr(arg, '='))
		return (FALSE);
	quoteless_arg = get_quoteless_str(arg);
	if (!quoteless_arg)
		return (TRUE);
	var_name = get_var_name(quoteless_arg);
	if (!var_name)
		return (free(quoteless_arg), TRUE);
	i = 0;
	while ((*envp)[i] && ft_strncmp((*envp)[i], var_name,
			ft_strlen(var_name)) != 0)
		i++;
	free(var_name);
	*envp = update_envp(quoteless_arg, envp, i);
	if (!*envp)
		return (TRUE);
	return (FALSE);
}

t_bool	export_builtin(t_lexer *lexer, char ***envp)
{
	if (lexer->options)
		return (perror_unexpected_option(),
			g_status = misuse_of_shell_builtins, TRUE);
	if (lexer && *(lexer->args + 2))
		return (perror_too_many_arguments(), g_status = general_failure, TRUE);
	if (lexer && !*(lexer->args + 1))
		return (env_builtin(lexer, envp));
	else if (lexer && export(*(lexer->args + 1), envp))
		return (g_status = general_failure, TRUE);
	return (FALSE);
}
