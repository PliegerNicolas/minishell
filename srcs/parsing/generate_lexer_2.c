/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_lexer_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 16:23:40 by nicolas           #+#    #+#             */
/*   Updated: 2023/03/23 19:19:16 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*retrieve_exec(char *cmd, size_t *i)
{
	int		start;
	int		len;

	if (!cmd)
		return (NULL);
	start = 0;
	len = 0;
	while (cmd[start] && ft_isspace(cmd[start]))
		start++;
	if (cmd[start] == '-')
		return (perror_command_not_found(), NULL);
	while (cmd[start + len] && !ft_isspace(cmd[start + len]))
		len++;
	*i += start + len;
	return (ft_substr(cmd, start, len));
}

static t_bool	next_char_is_dash(char *cmd)
{
	int	i;

	i = 0;
	while (ft_isspace(cmd[i]))
		i++;
	if (cmd[i] == '-')
		return (TRUE);
	return (FALSE);
}

static int	count_option_chars(char *cmd)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (next_char_is_dash(cmd + i))
	{
		while (cmd[i] && (ft_isspace(cmd[i]) || cmd[i] == '-'))
			i++;
		while (cmd[i] && !ft_isspace(cmd[i]))
		{
			i++;
			len++;
		}
	}
	return (len);
}

char	*retrieve_options(char *cmd, size_t *i)
{
	char	*options;
	int		j;
	int		len;

	if (!cmd)
		return (NULL);
	len = count_option_chars(cmd);
	options = malloc((len + 1) * sizeof(*options));
	if (!options)
		return (perror_malloc("@options (srcs/parsing/generate_lexer_2.c #retri\
eve_options)"), NULL);
	j = 0;
	len = 0;
	while (next_char_is_dash(cmd + j))
	{
		while (cmd[j] && (ft_isspace(cmd[j]) || cmd[j] == '-'))
			j++;
		while (cmd[j] && !ft_isspace(cmd[j]))
			options[len++] = cmd[j++];
	}
	options[len] = '\0';
	*i += j;
	return (options);
}

char	**retrieve_args(char *cmd, size_t *i)
{
	(void)i;
	(void)cmd;
	return (NULL);
}
