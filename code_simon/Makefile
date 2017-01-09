#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/13 10:42:48 by sgaudin           #+#    #+#              #
#    Updated: 2016/12/09 11:26:05 by sgaudin          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = 42sh

INCLUDES = ../includes/42sh.h ./includes/redir.h ./includes/globing.h

REDIR = ./redirections/
SBRACK = ./globing/square_brackets/
CBRACK = ./globing/curly_brackets/
UTILS_1 = ./globing/square_brackets/sbracket_utils/
UTILS_2 = ./globing/curly_brackets/cbracket_utils/
WILDCARDS = ./globing/wildcards/

SRCS =  main.c globing/glob_parser.c \
		\
		$(REDIR)simple_right.c $(REDIR)double_right.c $(REDIR)redir_utils.c\
		\
		$(SBRACK)hub_sbracket.c $(SBRACK)fill_tabs.c\
		$(SBRACK)init_tabs.c $(SBRACK)category_bracket.c\
		$(SBRACK)sbracket_list.c \
		\
		$(CBRACK)hub_cbracket.c $(CBRACK)fill_clist.c $(CBRACK)cbracket_list.c \
		$(CBRACK)cbracket_errors.c $(CBRACK)expansion.c \
		\
		$(UTILS_1)catch_dash.c $(UTILS_1)check_rng.c $(UTILS_1)clean_brackets.c\
		$(UTILS_1)count_brackets.c $(UTILS_1)get_functions.c\
		$(UTILS_1)str_nodouble.c \
		\
		$(UTILS_2)commas_utils.c $(UTILS_2)algo_imbricated.c $(UTILS_2)imbric_utils.c \
		$(UTILS_2)get_imbric_patterns.c $(UTILS_2)cbracket_utils.c \
		$(UTILS_2)imbric_utils2.c $(UTILS_2)double_brck.c $(UTILS_2)expansion_utils.c \
		\
		$(WILDCARDS)hub_final.c $(WILDCARDS)wildcards_tokens.c $(WILDCARDS)wildcards_utils.c\
		$(WILDCARDS)question_mark.c $(WILDCARDS)wildcards_utils2.c\
		$(GLOBING)globing/get_path.c  \

BIN =   main.o glob_parser.o \
		\
		simple_right.o double_right.o \
		redir_utils.o \
		\
		hub_sbracket.o fill_tabs.o \
		init_tabs.o \
		\
		category_bracket.o sbracket_list.o \
		catch_dash.o check_rng.o \
		clean_brackets.o count_brackets.o \
		get_functions.o str_nodouble.o \
		\
		hub_cbracket.o fill_clist.o \
		cbracket_list.o cbracket_errors.o \
		expansion.o \
		\
		commas_utils.o algo_imbricated.o \
		imbric_utils.o get_imbric_patterns.o \
		cbracket_utils.o imbric_utils2.o \
		double_brck.o expansion_utils.o \
		wildcards_tokens.o hub_final.o wildcards_utils.o\
		get_path.o question_mark.o wildcards_utils2.o


CC_FLAGS = -Wall -Wextra -Werror

LIBFT = ../libft/

all: $(NAME)

$(NAME):
	gcc $(CC_FLAGS) $(INCLUDES) $(SRCS) -c
	gcc $(CC_FLAGS) $(BIN) $(LIBFT)libft.a -o $(NAME)
	mkdir bin_folder
	mv $(BIN) bin_folder

libft:
	make -C $(LIBFT)
	gcc $(CC_FLAGS) $(INCLUDES) $(SRCS) -c
	gcc $(CC_FLAGS) $(BIN) $(LIBFT)libft.a -o $(NAME)
	mkdir bin_folder
	mv $(BIN) bin_folder

clean:
	rm -rf bin_folder

clean_lib:
	make -C $(LIBFT) clean

fclean: clean
	rm -rf $(NAME)
	sh ../rm_files.sh

fclean_lib: clean_lib
	make -C $(LIBFT) fclean

re: fclean all

re_lib: fclean_lib libft
