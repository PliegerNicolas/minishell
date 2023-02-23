/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:17:16 by nplieger          #+#    #+#             */
/*   Updated: 2023/02/23 15:11:02 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
# define MINISHELL_H

/* ************************************** */
/* * INCLUDES							* */
/* ************************************** */

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

/* ************************************** */
/* * TYPEDEFS							* */
/* ************************************** */

typedef struct s_options
{
	char		*temp_arg;
}	t_options;

typedef struct s_command
{
	char				*temp_arg;
	t_options			options;
	struct s_command	*next;
}	t_command;

/* ************************************** */
/* * COLORS								* */
/* ************************************** */

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define LIGHT_GRAY "\033[0;37m"
# define DARK_GRAY "\033[0;38m"
# define WHITE "\033[0m"

/* ************************************** */
/* * FUNCTIONS							* */
/* ************************************** */

#endif
