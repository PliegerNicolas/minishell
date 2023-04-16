# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nplieger <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/22 11:23:54 by nplieger          #+#    #+#              #
#    Updated: 2023/04/16 17:37:04 by nicolas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				:=		minishell

#------------------------------------------------#
#   PATHS                                        #
#------------------------------------------------#

SRC_DIR				:=		srcs
OBJ_DIR				:=		objs
INC_DIR				:=		includes

#------------------------------------------------#
#   INGREDIENTS                                  #
#------------------------------------------------#

SRCS				:=		minishell \
							env/initialize_env \
							env/env_utils \
							env/free_env \
							env/get_env_var \
							env/set_env_var \
							env/remove_env_var \
							output/prompt_prefix \
							output/error_messages_1 \
							output/error_messages_2 \
							output/error_messages_3 \
							output/utils/ft_putchar_fd \
							output/utils/ft_putstr_fd \
							output/utils/ft_putendl_fd \
							output/utils/ft_putnbr_fd \
							output/utils/write_colors \
							signals/sig_handlers \
							signals/echoctl_handlers \
							execution/executer \
							execution/builtin_execution \
							execution/external_command_execution \
							execution/utils \
							execution/builtins/is_builtin \
							execution/builtins/echo_builtin \
							execution/builtins/cd_builtin \
							execution/builtins/pwd_builtin \
							execution/builtins/export_builtin \
							execution/builtins/unset_builtin \
							execution/builtins/env_builtin \
							execution/builtins/exit_builtin \
							parsing/parse_user_input \
							parsing/substitute_variables_1 \
							parsing/substitute_variables_2 \
							parsing/generate_commands \
							parsing/generate_lexer \
							parsing/populate_lexer \
							parsing/set_exec \
							parsing/set_options \
							parsing/set_arguments \
							parsing/set_redirection_1 \
							parsing/set_redirection_2 \
							parsing/quote \
							parsing/ft_setsplit_quotesafe \
							parsing/free_commands \
							utils/ft_strchr \
							utils/ft_substr \
							utils/ft_strjoin \
							utils/ft_split \
							utils/ft_strdup \
							utils/ft_strlcpy \
							utils/ft_strlen \
							utils/ft_strtrim \
							utils/ft_bzero \
							utils/ft_calloc \
							utils/ft_strncmp \
							utils/ft_isspace \
							utils/ft_strlcat \
							utils/ft_setsplit \
							utils/ft_trimsplit \
							utils/ft_strnstr \
							utils/ft_memcpy \
							utils/ft_itoa \
							utils/ft_isalpha \
							utils/ft_followed_chars \
							utils/ft_isnextcharset \
							utils/ft_prepend_to_string_array \
							utils/ft_append_to_string_array \
							utils/ft_join_str_arr \

DEPS				:=		minishell \

SRCS_C				:=		$(addsuffix .c, $(SRCS))
CC_SRCS_C			:=		$(addsuffix $(SRC_DIR)/, $(SRCS_C))

DEPS_H				:=		$(addsuffix .h, $(DEPS))
CC_DEPS_H			:=		$(addsuffix $(DEPS_H), $(INC_DIR)/)

OBJS				:=		$(SRCS_C:%.c=$(OBJ_DIR)/%.o)

#------------------------------------------------#
#   COMMANDS                                     #
#------------------------------------------------#

CC					:=		gcc
AR					:=		ar -rcs
INCS				:=		-I $(INC_DIR)
CFLAGS				:=		-Wall -Wextra -Werror -g3 #-O3
RM					:=		rm -f

#------------------------------------------------#
#   RECIPES                                      #
#------------------------------------------------#

all:				$(NAME)

$(NAME):			$(OBJS)
	$(AR) $(NAME).a $(OBJS)
	$(CC) $(CFLAGS) $(NAME).a -lreadline -o ./$(NAME)

$(OBJS):			$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(CC_DEPS_H)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCS) -c $< -lreadline -o $@

clean:
	$(RM) -r $(OBJ_DIR)

fclean:				clean
	$(RM) $(NAME).a
	$(RM) $(NAME)

re:					fclean all

.PHONY: all clean fclean re
