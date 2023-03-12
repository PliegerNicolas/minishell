/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:17:16 by nplieger          #+#    #+#             */
/*   Updated: 2023/03/12 20:01:57 by nicolas          ###   ########.fr       */
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
# include <termios.h>

/* ************************************** */
/* * ENUMERATORS						* */
/* ************************************** */

enum e_status
{
	success = 1,
	failure = 2
};

/* ************************************** */
/* * TYPEDEFS							* */
/* ************************************** */

typedef int		t_bool;

typedef struct s_lexer
{
	char				*exec;
	char				*options;
	char				**args;
	struct s_lexer		*previous;
	struct s_lexer		*next;
}	t_lexer;

typedef struct s_commands
{
	t_lexer				*lexer;
	struct s_commands	*next;
}	t_commands;

/* ************************************** */
/* * GLOBAL VAR							* */
/* ************************************** */

/* ************************************** */
/* * MACRO								* */
/* ************************************** */

/* std */

# define STDIN 0
# define STDOUT 1
# define STDERR 2

/* t_bool */

# define FALSE 0
# define TRUE 1

/* int limits */

# define MAX_INT 2147483647
# define MIN_INT -2147483648

/* buffer_size */

# define BUFFER_SIZE 4096

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

char			**initialize_env(int argc, char **argv, char **env);
void			put_env(char **envp);
size_t			env_len(char **envp);
void			free_envp(char **envp);

/* ouput */

char			*prompt_prefix(enum e_status status);

void			perror_minishell_arguments(int nbr_args);
void			perror_environnement_copy(void);
void			perror_malloc(char *location);

int				ft_putchar_fd(char c, int fd);
int				ft_putstr_fd(char *s, int fd);
int				ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
int				set_write_color(char *s, int fd);
int				reset_write_color(int fd);

/* signals */

void			setup_signals(void);
void			reset_signals(void);

void			rm_echoctl(void);
void			reset_echoctl(void);

/* lexical_analysis */

t_commands		*lexer(char *line);
t_commands		*initialize_commands(char *line);
void			free_commands(t_commands *commands);

/* execution */

enum e_status	exec(char **envp, char *line);

/* utils */

char			*ft_strchr(const char *s, int c);
char			*ft_substr(const char *s, unsigned int start, size_t len);
char			**ft_split(char const *s, char c);
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
char			*ft_strtrim(char const *s1, char const *set);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_isspace(int c);

void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t count, size_t size);

size_t			ft_sections(const char *s, const char *set);

#endif
