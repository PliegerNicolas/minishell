/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:17:16 by nplieger          #+#    #+#             */
/*   Updated: 2023/03/07 23:25:48 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
# define MINISHELL_H

/* ************************************** */
/* * INCLUDES							* */
/* ************************************** */

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

/* ************************************** */
/* * GLOBAL VAR							* */
/* ************************************** */

extern char	**g_envp;

/* ************************************** */
/* * ENUMERATORS						* */
/* ************************************** */

/* ************************************** */
/* * TYPEDEFS							* */
/* ************************************** */

typedef int	t_bool;

/* ************************************** */
/* * MACRO								* */
/* ************************************** */

/* t_bool */

# define FALSE 0
# define TRUE 1

/* int limits */

# define MAX_INT 2147483647
# define MIN_INT -2147483648

/* colors */

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

/* env */

t_bool	initialize_env(int argc, char **argv, char **env);
void	put_env(void);
size_t	env_len(char **env);

/* signals */

/* parsing */

/* utils */

void	free_g_envp(void);

char	*ft_strchr(const char *s, int c);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strtrim(char const *s1, char const *set);

void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);

int		ft_putchar_fd(char c, int fd);
int		ft_putstr_fd(char *s, int fd);
int		ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	set_write_color(char *s, int fd);
void	reset_write_color(int fd);

#endif
