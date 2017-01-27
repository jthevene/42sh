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

DIEUSON 			=	./
SRC_DIR				=	$(DIEUSON)line_edition/
INCLUDE_DIR			=	$(DIEUSON)includes
OBJ_DIR				=	./objs
DIR_AUTO 			= 	$(DIEUSON)completion_dynamique/

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
						$(DIR_AUTO)detect_auto_completion.c $(DIR_AUTO)get_files.c \
						$(DIR_AUTO)match_elements.c $(DIR_AUTO)set_path.c \
						$(DIR_AUTO)display_completion.c $(DIR_AUTO)build_list.c \
						$(DIR_AUTO)set_sentence.c $(DIR_AUTO)free_auto_completion.c \
						$(DIR_AUTO)tools.c $(DIR_AUTO)set_path_second_part.c

BIN_DIEUSON 		=	main.o catch_key.o 	\
						cursor_move.o history.o \
						init.o copy_cut_past.o \
						line_edition.o print_line.o \
						return_key.o signal.o \
						termios.o var.o history2.o\
						detect_auto_completion.o get_files.o \
						match_elements.o set_path.o display_completion.o \
						build_list.o set_sentence.o free_auto_completion.o \
						tools.o set_path_second_part.o

################# 		GLOBING PART		####################################

GLOBING = ./code_simon/
REDIR = $(GLOBING)redirections/
SBRACK = $(GLOBING)globing/square_brackets/
CBRACK = $(GLOBING)globing/curly_brackets/
WILDCARDS = $(GLOBING)globing/wildcards/
UTILS_1 = $(GLOBING)globing/square_brackets/sbracket_utils/
UTILS_2 = $(GLOBING)globing/curly_brackets/cbracket_utils/
BIN_DIR_GLOBING = $(GLOBING)bin_folder/

SRC_GLOBING = $(GLOBING)globing/glob_parser.c $(GLOBING)globing/get_path.c \
		$(GLOBING)globing/verif_tokens.c \
		\
		$(REDIR)simple_right.c $(REDIR)double_right.c $(REDIR)redir_utils.c \
		\
		$(SBRACK)hub_sbracket.c $(SBRACK)fill_tabs.c \
		$(SBRACK)init_tabs.c $(SBRACK)category_bracket.c \
		$(SBRACK)sbracket_list.c \
		\
		$(CBRACK)hub_cbracket.c $(CBRACK)fill_clist.c $(CBRACK)cbracket_list.c \
		$(CBRACK)cbracket_errors.c $(CBRACK)expansion.c $(CBRACK)print_clist.c \
		\
		$(UTILS_1)catch_dash.c $(UTILS_1)check_rng.c $(UTILS_1)clean_brackets.c \
		$(UTILS_1)count_brackets.c $(UTILS_1)get_functions.c \
		$(UTILS_1)str_nodouble.c \
		\
		$(UTILS_2)commas_utils.c $(UTILS_2)algo_imbricated.c $(UTILS_2)imbric_utils.c \
		$(UTILS_2)get_imbric_patterns.c $(UTILS_2)cbracket_utils.c \
		$(UTILS_2)imbric_utils2.c $(UTILS_2)double_brck.c $(UTILS_2)expansion_utils.c \
		\
		$(WILDCARDS)hub_final.c $(WILDCARDS)wildcards_tokens.c $(WILDCARDS)wildcards_utils.c \
		$(WILDCARDS)wildcards_utils2.c $(WILDCARDS)lst_tools.c $(WILDCARDS)check_file.c \

BIN_GLOBING = glob_parser.o get_path.o verif_tokens.o \
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
		expansion.o print_clist.o \
		\
		commas_utils.o algo_imbricated.o \
		imbric_utils.o get_imbric_patterns.o \
		cbracket_utils.o imbric_utils2.o \
		double_brck.o expansion_utils.o \
		wildcards_tokens.o hub_final.o wildcards_utils.o\
		wildcards_utils2.o lst_tools.o check_file.o
		
################# 		END GLOBING PART		####################################

################# 			PARSER PART			####################################
PARSER = ./Lexer_Parser/srcs/

SRC_PARSER = $(PARSER)backslash_escape.c $(PARSER)free_tree.c \
			$(PARSER)isallspace.c $(PARSER)lexer_check.c $(PARSER)parser_distrib.c $(PARSER)parse.c \
			$(PARSER)start_parse.c $(PARSER)tree.c 

BIN_PARSER = backslash_escape.o free_tree.o isallspace.o lexer_check.o \
			 parser_distrib.o parse.o start_parse.o tree.o



################# 		END PARSER PART			####################################

#################		BUILTIN PART 			####################################

SRC_BUILTIN = builtins/echo.c builtins/env.c builtins/setenv.c builtins/unsetenv.c \
				builtins/cd.c builtins/path_converter.c

BIN_BUILTIN = echo.o env.o setenv.o unsetenv.o cd.o path_converter.o

#################		END BUILTIN PART 		####################################

INCLUDES 	= -I$(INCLUDE_DIR) -I$(LIBFT_INCLUDE_DIR) \
			-I$(GLOBING)includes/ -I$(PARSER)includes/sh.h

all: $(NAME)

lib:
	make -C libft

$(NAME):
	gcc $(C_FLAGS) $(INCLUDES) $(SRC_DIEUSON) $(SRC_GLOBING) $(SRC_PARSER) $(SRC_BUILTIN) -Incurses -c
	gcc $(C_FLAGS) $(BIN_GLOBING) $(BIN_DIEUSON) $(BIN_BUILTIN) $(BIN_PARSER) $(LIBFT_DIR)/libftprintf.a \
			$(LIBFT_DIR)/libft.a -ltermcap -o $(NAME)
	mkdir bin_folder
	mv $(BIN_DIEUSON) $(BIN_GLOBING) $(BIN_BUILTIN) $(BIN_PARSER) bin_folder

clean:
	make -C $(GLOBING) clean
	rm -rf bin_folder

clean_lib:
	make -C $(LIBFT_DIR) clean

fclean: clean
	make -C $(GLOBING) fclean
	rm -rf $(NAME)
	sh ./rm_files.sh

fclean_lib: clean_lib
	make -C $(LIBFT_DIR) fclean

re: fclean all

re_lib: fclean_lib lib