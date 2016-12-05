#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/13 10:43:29 by sgaudin           #+#    #+#              #
#    Updated: 2016/10/13 10:43:29 by sgaudin          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME				=	42sh

DIEUSON 			=	./code_dieuson/
SRC_DIR				=	$(DIEUSON)srcs/
INCLUDE_DIR			=	$(DIEUSON)includes
OBJ_DIR				=	./objs

LIBFT_DIR			=	./libft
LIBFT_NAME			=	$(LIBFT_DIR)/libft.a
LIBFT_INCLUDE_DIR	=	$(LIBFT_DIR)/includes

COMPILER			=	gcc
C_FLAGS				=	-g3 -O3 -Wall -Wextra -Werror
LFLAGS				=	-L$(LIBFT_DIR) -l$(LIBFT)

SRC_DIEUSON			=	$(SRC_DIR)main.c $(SRC_DIR)catch_key.c 	\
						$(SRC_DIR)cursor_move.c $(SRC_DIR)history.c \
						$(SRC_DIR)init.c $(SRC_DIR)copy_cut_past.c \
						$(SRC_DIR)line_edition.c $(SRC_DIR)print_line.c \
						$(SRC_DIR)return_key.c $(SRC_DIR)signal.c \
						$(SRC_DIR)termios.c $(SRC_DIR)var.c \
						$(SRC_DIR)history2.c \

BIN_DIEUSON 		=	main.o catch_key.o 	\
						cursor_move.o history.o \
						init.o copy_cut_past.o \
						line_edition.o print_line.o \
						return_key.o signal.o \
						termios.o var.o history2.o\

################# 		SIMON PART		####################################
SIMON = ./code_simon/
REDIR = $(SIMON)redirections/
SBRACK = $(SIMON)globing/square_brackets/
CBRACK = $(SIMON)globing/curly_brackets/
UTILS_1 = $(SIMON)globing/square_brackets/sbracket_utils/
UTILS_2 = $(SIMON)globing/curly_brackets/cbracket_utils/
BIN_DIR_SIMON = $(SIMON)bin_folder/

BIN_SIMON =	$(BIN_DIR_SIMON)glob_parser.o \
		\
		$(BIN_DIR_SIMON)simple_right.o $(BIN_DIR_SIMON)double_right.o \
		$(BIN_DIR_SIMON)redir_utils.o \
		\
		$(BIN_DIR_SIMON)hub_sbracket.o $(BIN_DIR_SIMON)fill_tabs.o \
		$(BIN_DIR_SIMON)init_tabs.o \
		\
		$(BIN_DIR_SIMON)category_bracket.o $(BIN_DIR_SIMON)sbracket_list.o \
		$(BIN_DIR_SIMON)catch_dash.o $(BIN_DIR_SIMON)check_rng.o \
		$(BIN_DIR_SIMON)clean_brackets.o $(BIN_DIR_SIMON)count_brackets.o \
		$(BIN_DIR_SIMON)get_functions.o $(BIN_DIR_SIMON)str_nodouble.o \
		\
		$(BIN_DIR_SIMON)hub_cbracket.o $(BIN_DIR_SIMON)fill_clist.o \
		$(BIN_DIR_SIMON)cbracket_list.o $(BIN_DIR_SIMON)cbracket_errors.o \
		$(BIN_DIR_SIMON)expansion.o \
		\
		$(BIN_DIR_SIMON)commas_utils.o $(BIN_DIR_SIMON)algo_imbricated.o \
		$(BIN_DIR_SIMON)imbric_utils.o $(BIN_DIR_SIMON)get_imbric_patterns.o \
		$(BIN_DIR_SIMON)cbracket_utils.o $(BIN_DIR_SIMON)imbric_utils2.o \
		$(BIN_DIR_SIMON)double_brck.o $(BIN_DIR_SIMON)expansion_utils.o
################# 		END SIMON PART		####################################

INCLUDES 	= -I$(INCLUDE_DIR) -I$(LIBFT_INCLUDE_DIR) \
			-I$(SIMON)includes/

all: $(NAME)

libft:
	make -C $(LIBFT)

$(NAME): libft
	make -C $(SIMON)
	gcc $(C_FLAGS) $(INCLUDES) $(SRC_DIEUSON) -Incurses -c
	gcc $(C_FLAGS)  $(BIN_SIMON) $(BIN_DIEUSON) $(LIBFT_DIR)/libft.a -ltermcap -o $(NAME)
	mkdir bin_folder
	mv $(BIN_DIEUSON) bin_folder

clean:
	make -C $(SIMON) clean
	rm -rf bin_folder

clean_lib:
	make -C $(LIBFT_DIR) clean

fclean: clean
	make -C $(SIMON) fclean
	rm -rf $(NAME)
	sh ./rm_files.sh

fclean_lib: clean_lib
	make -C $(LIBFT_DIR) fclean

re: fclean all

re_lib: fclean_lib libft