# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: osarsar <osarsar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/16 03:20:46 by osarsar           #+#    #+#              #
#    Updated: 2023/08/16 03:20:46 by osarsar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	main.c				\
		execution/minishell.c			\
		execution/exec_path.c	\
		execution/split.c		\
		execution/minishell_utils.c	\
		execution/create_node.c	\
		execution/minishell_utils2.c	\
		parsing/grb_collector_linkd_list.c \
		parsing/utils1.c			\
		parsing/utils2.c			\
		parsing/linked_list_cmd.c	\
		parsing/linked_list_env.c		\
		parsing/linked_list_lexer.c	\
		execution/builtins.c			\
		execution/builtins_utils.c			\

READLINE = $(shell brew --prefix readline)
NAME = mini.a
FLAGS = -Wall -Werror -Wextra -I$(READLINE)/include -g -fsanitize=address
%.o : %.c minishell.h
	@echo "Compiling: $<"
	@cc $(FLAGS)  -c $< -o $@

$(NAME) : $(SRCS:.c=.o)
	@ar -r $(NAME) $(SRCS:.c=.o)
	@cc main.c  $(FLAGS)  $(NAME) -lreadline  -L$(READLINE)/lib -o minishell

all : $(NAME)

clean :
	@rm -f $(SRCS:.c=.o)

fclean : clean
	@rm -f mini.a

re : fclean all