/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:17:16 by nplieger          #+#    #+#             */
/*   Updated: 2023/02/23 15:14:45 by nicolas          ###   ########.fr       */
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

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define PURPLE "\033[1;35m"
# define CYAN "\033[1;36m"
# define LIGHT_GRAY "\033[1;37m"
# define DARK_GRAY "\033[1;38m"
# define WHITE "\033[0m"

/* ************************************** */
/* * FUNCTIONS							* */
/* ************************************** */

#endif
