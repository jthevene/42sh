#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/13 10:42:48 by sgaudin           #+#    #+#              #
#    Updated: 2016/10/13 10:44:40 by sgaudin          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = 42sh

INCLUDES = ../includes/42sh.h ./includes/redir.h

REDIR = ./redirections/
GLOB = ./globing/

SRCS = 	$(REDIR)simple_right.c $(REDIR)double_right.c $(REDIR)redir_utils.c\
		$(GLOB)glob_parser.c $(GLOB)square_brackets.c $(GLOB)fill_glob_struct.c\
		$(GLOB)init_tabs.c $(GLOB)brackets_cases.c main.c

BIN =	simple_right.o double_right.o redir_utils.o main.o glob_parser.o \
		square_brackets.o fill_glob_struct.o init_tabs.o brackets_cases.o

CC_FLAGS = -Wall -Wextra -Werror

LIBFT = ../libft/

all: $(NAME)

$(NAME):
	make -C $(LIBFT)
	gcc $(CC_FLAGS) $(INCLUDES) $(SRCS) -c
	gcc $(CC_FLAGS) $(BIN) $(LIBFT)libft.a -o $(NAME)
	mkdir bin_folder
	mv $(BIN) bin_folder

clean:
	rm -rf bin_folder
	make -C $(LIBFT) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(LIBFT) fclean

re: fclean all