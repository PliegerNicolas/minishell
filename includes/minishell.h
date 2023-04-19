/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:17:16 by nplieger          #+#    #+#             */
/*   Updated: 2023/04/19 15:40:18 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
# define MINISHELL_H

/* ************************************** */
/* * INCLUDES							* */
/* ************************************** */

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <termios.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <errno.h>

/* ************************************** */
/* * ENUMERATORS						* */
/* ************************************** */

enum e_status
{
	success = 0,
	general_failure = 1,
	misuse_of_shell_builtins = 2,
	command_invoked_cannot_execute = 126,
	command_not_found = 127,
	invalid_argument_to_exit = 128,
	termination_by_ctrl_c = 130,
	exit_status_out_of_range = 255,
	exit_program = 256
};

enum e_quote_status
{
	none = 0,
	single_quote = 1,
	double_quote = 2
};

enum e_redir_type
{
	no_redir = 0,
	to_file = 1,
	append_to_file = 2,
	from_file = 3,
	heredoc = 4
};

/* ************************************** */
/* * TYPEDEFS							* */
/* ************************************** */

typedef int				t_bool;

typedef struct s_lexer
{
	size_t				id;
	char				*cmd;
	char				*exec;
	char				**options;
	char				**args;
	enum e_redir_type	redir_type[2];	
	char				*redir_path[2];
	int					pipe[2];
	struct s_lexer		*previous;
	struct s_lexer		*next;
}	t_lexer;

typedef struct s_commands
{
	char				*cmd;
	t_lexer				*lexer;
	struct s_commands	*next;
}	t_commands;

/* ************************************** */
/* * GLOBAL VAR							* */
/* ************************************** */

extern enum e_status	g_status;

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

/* whitespaces */

# define WHITE_SPACES " \t\n\v\f\r"

/* buffer_size */

# define BUFFER_SIZE 4096

/* colors */

# define RED "\001\033[1;31m\002"
# define GREEN "\001\033[1;32m\002"
# define YELLOW "\001\033[1;33m\002"
# define BLUE "\001\033[1;34m\002"
# define PURPLE "\001\033[1;35m\002"
# define CYAN "\001\033[1;36m\002"
# define LIGHT_GRAY "\001\033[1;37m\002"
# define DARK_GRAY "\001\033[1;38m\002"
# define WHITE "\001\033[0m\002"

/* ************************************** */
/* * FUNCTIONS							* */
/* ************************************** */

/* env */

char			**initialize_env(int argc, char **argv, char **env);

char			*get_env_var(const char *var, const char **envp);
char			**set_env_var(char *name, char *value, char **envp);
char			**remove_env_var(char *var_name, char **envp);

void			put_env(char **envp);
size_t			env_len(char **envp);
void			free_envp(char **envp);

/* ouput */

char			*prompt_prefix(void);

void			perror_minishell_arguments(int nbr_args);
void			perror_environnement(void);
void			perror_malloc(char *location);
void			perror_bad_substitution(void);
void			perror_quote(void);
void			perror_command_not_found(void);
void			perror_invalid_options(void);
void			perror_parse_error(void);
void			perror_file(void);
void			perror_unexpected_option(void);
void			perror_too_many_arguments(void);
void			perror_not_enough_arguments(void);
void			perror_no_such_file_or_dir(char *path);

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

/* execution */

enum e_status	executer(char ***envp, char *line);
void			close_fds(int *pipefds, int *previous_fd);
t_bool			is_builtin(const char *str);
t_bool			builtin_execution(t_lexer *lexer, int *prev_fd, char ***envp);
t_bool			external_execution(t_lexer *lexer, int *prev_fd, char ***envp);

void			put_fd(int fd);
int				open_file(const char *path, const enum e_redir_type redir_type);
void			close_fds(int *pipefds, int *prev_fd);

t_bool			echo_builtin(t_lexer *lexer);
t_bool			cd_builtin(t_lexer *lexer, char ***envp);
t_bool			pwd_builtin(t_lexer *lexer);
t_bool			export_builtin(t_lexer *lexer, char ***envp);
t_bool			unset_builtin(t_lexer *lexer, char ***envp);
t_bool			env_builtin(t_lexer *lexer, char ***envp);
t_bool			exit_builtin(void);

/* parsing */

t_commands		*parse_user_input(char *line, char ***envp);
t_commands		*generate_commands(const char *line, char ***envp);
t_lexer			*generate_lexer(const char *cmd, char ***envp);
t_lexer			*populate_lexer(t_lexer *lexer, const char *cmd,
					enum e_quote_status quote_status, char ***envp);

t_bool			set_exec(const char *str, t_lexer *lexer,
					t_bool *prev_is_redir, char ***envp);
t_bool			set_options(const char *str, t_lexer *lexer);
t_bool			set_arguments(const char *str, t_lexer *lexer);
t_bool			set_redirection(const char *str, t_lexer *lexer,
					t_bool *prev_is_redir);

t_bool			set_redir_path(char *pathname, t_lexer *lexer, int slot);
t_bool			set_redir_path_heredoc(const char *end, t_lexer *lexer);

char			*substitute_line_content(char *line, size_t i,
					enum e_quote_status quote_status);
char			**set_var_landmarks(char *line, size_t i, size_t len,
					t_bool brackets);
size_t			get_placeholder_len(char *line, size_t i, t_bool brackets);

t_bool			set_quotestatus(char *s, enum e_quote_status *quote_status);
t_bool			quote_error(char *s, enum e_quote_status quote_status);
char			*remove_quotes(char *line, enum e_quote_status quote_status);
char			**ft_setsplit_quotesafe(const char *line, const char *set,
					enum e_quote_status quote_status);

void			free_commands(t_commands *commands);
void			free_lexer(t_lexer *lexer);
void			free_str_arr(char **arr);

/* utils */

char			*ft_strchr(const char *s, int c);
char			*ft_substr(const char *s, unsigned int start, size_t len);
char			**ft_split(char const *s, char c);
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
char			*ft_strtrim(char const *s1, char const *set);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_isspace(int c);
char			*ft_strnstr(const char *big, const char *little, size_t len);
void			*ft_memcpy(void *dest, const void *src, size_t n);
char			*ft_itoa(int n);
int				ft_isalpha(int c);
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t count, size_t size);

char			**ft_join_str_arr(char **arr1, char **arr2);
char			**ft_append_to_string_array(char **str_arr, char *str);
char			**ft_prepend_to_string_array(char **str_arr, char *str);
char			**ft_setsplit(const char *line, const char *set);
char			**ft_trimsplit(const char **split, const char *set);
int				ft_followed_chars(const char *s, const int c1, const int c2);
int				ft_isnextcharset(const char *s, const char *set);
size_t			ft_strarrlen(const char **strarr);

#endif
