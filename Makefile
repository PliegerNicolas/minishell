# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nicolas <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/21 15:02:08 by nicolas           #+#    #+#              #
#    Updated: 2023/05/21 20:45:17 by nicolas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#* ************************************************************************** *#
#* *                                 UTILS                                  * *#
#* ************************************************************************** *#

NAME			=			minishell
AR				=			ar -rcs
CC				=			gcc
CFLAGS			=			
RUN_PARAM		=			

#* ************************************************************************** *#
#* *                                SOURCES                                 * *#
#* ************************************************************************** *#

SRCS_EXTENSION	=			.c
SRCS_PATH		=			./srcs
MAIN_NAME		=			$(NAME)

SRCS_NAMES		=			minishell \
							signals/sig_handlers \
							signals/echoctl_handlers \
							output/prompt_prefix \
							output/utils/ft_putchar_fd \
							output/utils/ft_putstr_fd \
							output/utils/ft_putendl_fd \
							output/utils/ft_putnbr_fd \
							output/utils/write_colors \
							output/error_messages_1 \
							output/error_messages_2 \
							output/error_messages_3 \
							env/initialize_env \
							env/get_env_var \
							env/set_env_var \
							env/remove_env_var \
							env/env_utils \
							env/free_env \
							execution/executer \
							execution/builtin_execution \
							execution/external_command_execution \
							execution/builtins/is_builtin \
							execution/builtins/echo_builtin \
							execution/builtins/cd_builtin \
							execution/builtins/pwd_builtin \
							execution/builtins/export_builtin \
							execution/builtins/unset_builtin \
							execution/builtins/env_builtin \
							execution/builtins/exit_builtin \
							execution/utils \
							parsing/parse_user_input \
							parsing/ft_setsplit_quotesafe \
							parsing/generate_commands \
							parsing/generate_lexer \
							parsing/populate_lexer \
							parsing/set_exec \
							parsing/get_path \
							parsing/set_options \
							parsing/set_arguments \
							parsing/set_redirection_1 \
							parsing/set_redirection_2 \
							parsing/set_heredoc_1 \
							parsing/set_heredoc_2 \
							parsing/destroy_heredocs \
							parsing/substitute_variables_1 \
							parsing/substitute_variables_2 \
							parsing/get_quoteless_str \
							parsing/remove_quotes \
							parsing/free_commands \
							utils/replace_first \
							utils/ft_prepend_to_string_array \
							utils/ft_append_to_string_array \
							utils/ft_join_str_arr \
							utils/ft_strarrlen \
							utils/is_inset \
							utils/ft_followed_chars \
							utils/ft_isnextcharset \
							utils/ft_only_whitespace \
							utils/ft_trimsplit \
							utils/ft_strjoin \
							utils/ft_setsplit \
							utils/ft_split \
							utils/ft_strdup \
							utils/ft_substr \
							utils/ft_strtrim \
							utils/ft_strchr \
							utils/ft_strlcpy \
							utils/ft_strlen \
							utils/ft_bzero \
							utils/ft_calloc \
							utils/ft_strncmp \
							utils/ft_isspace \
							utils/ft_strlcat \
							utils/ft_strnstr \
							utils/ft_memcpy \
							utils/ft_itoa \
							utils/ft_isalpha \
							utils/ft_atolli \

#* ************************************************************************** *#
#* *                               INCLUDES                                 * *#
#* ************************************************************************** *#

INCLUDE_DIRS	=			includes

#* ************************************************************************** *#
#* *                                OBJECTS                                 * *#
#* ************************************************************************** *#

OBJS_PATH		=			./objs

MAIN			=			$(addsuffix $(SRCS_EXTENSION), $(MAIN_NAME))
SRCS			=			$(addsuffix $(SRCS_EXTENSION), $(SRCS_NAMES))

OBJS			=			$(addprefix $(OBJS_PATH)/, ${SRCS:$(SRCS_EXTENSION)=.o})
OBJ_MAIN		=			$(addprefix $(OBJS_PATH)/, ${MAIN:$(SRCS_EXTENSION)=.o})
OBJS_DEPEND		=			$(addprefix $(OBJS_PATH)/, ${SRCS:$(SRCS_EXTENSION)=.d})
OBJ_MAIN_DEPEND	=			$(addprefix $(OBJS_PATH)/, ${MAIN:$(SRCS_EXTENSION)=.d})

INCLUDE_FLAGS	=			$(addprefix -I , ${INCLUDE_DIRS})

#* ************************************************************************** *#
#* *                               CONSTANTS                                * *#
#* ************************************************************************** *#

BLUE			=			\033[1;34m
CYAN			=			\033[0;36m
GREEN			=			\033[0;32m
ORANGE			=			\033[0;33m
NO_COLOR		=			\033[m

#* ************************************************************************** *#
#* *                                MAKEFILE                                * *#
#* ************************************************************************** *#

ifeq (noflag, $(filter noflag,$(MAKECMDGOALS)))
	CFLAGS		+=			-Wall -Wextra
else
	CFLAGS		+=			-Wall -Wextra -Werror
endif

ifeq (debug, $(filter debug,$(MAKECMDGOALS)))
	CFLAGS		+=			-g3
endif

ifeq (sanaddress, $(filter sanaddress,$(MAKECMDGOALS)))
	CFLAGS		+=			-fsanitize=address
endif

ifeq (santhread, $(filter santhread,$(MAKECMDGOALS)))
	CFLAGS		+=			-fsanitize=thread
endif

#* ************************************************************************** *#
#* *                                 RULES                                  * *#
#* ************************************************************************** *#

all:				$(NAME)

# ----- #

$(OBJS_PATH)/%.o:	$(SRCS_PATH)/%$(SRCS_EXTENSION)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -MF $(@:.o=.d) ${INCLUDE_FLAGS} -c $< -o $@

# ----- #

clean:
	rm -rf $(OBJS_PATH)

fclean:				clean
	rm -f $(NAME).a
	rm -f $(NAME)

re:					fclean all

# ----- #

-include $(OBJS_DEPEND) $(OBJ_MAIN_DEPEND)
$(NAME):			${OBJS} ${OBJ_MAIN}
	$(AR) $(NAME).a ${OBJS} ${OBJ_MAIN}
	$(CC) $(CFLAGS) $(INCLUDE_FLAGS) $(NAME).a -lreadline -o $@

# ----- #

run:				all
	./$(NAME) $(RUN_PARAM)

noflag:				all

debug:				all

sanaddress:			all

santhread:			all

# ----- #

.PHONY: all clean fclean re run debug sandaddress santhread
