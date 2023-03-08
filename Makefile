# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nplieger <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/22 11:23:54 by nplieger          #+#    #+#              #
#    Updated: 2023/03/08 18:30:47 by nicolas          ###   ########.fr        #
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
							utils/ft_strchr \
							utils/ft_substr \
							utils/ft_split \
							utils/ft_strdup \
							utils/ft_strlcpy \
							utils/ft_strlen \
							utils/ft_strtrim \
							utils/ft_bzero \
							utils/ft_calloc \
							utils/ft_putchar_fd \
							utils/ft_putstr_fd \
							utils/ft_putendl_fd \
							utils/ft_putnbr_fd \
							utils/write_colors \

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
