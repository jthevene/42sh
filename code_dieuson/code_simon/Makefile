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

INCLUDES = ../includes/42sh.h ./includes/redir.h ./includes/globing.h

REDIR = ./redirections/
GLOB = ./globing/
G_UTILS1 = ./globing/sbracket_utils/

SRCS = 	$(REDIR)simple_right.c $(REDIR)double_right.c $(REDIR)redir_utils.c\
		\
		$(GLOB)glob_parser.c $(GLOB)hub_bracket.c $(GLOB)fill_tabs.c\
		$(GLOB)init_tabs.c $(GLOB)category_bracket.c\
		$(GLOB)sbracket_list.c \
		\
		$(G_UTILS1)catch_dash.c $(G_UTILS1)check_rng.c $(G_UTILS1)clean_brackets.c\
		$(G_UTILS1)count_brackets.c $(G_UTILS1)get_functions.c\
		$(G_UTILS1)str_nodouble.c\
		\
		main.c

BIN =	simple_right.o double_right.o redir_utils.o main.o glob_parser.o \
		hub_bracket.o fill_tabs.o init_tabs.o \
		category_bracket.o sbracket_list.o catch_dash.o check_rng.o \
		clean_brackets.o count_brackets.o get_functions.o str_nodouble.o


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