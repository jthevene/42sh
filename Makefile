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

INCLUDE_DIR			=	./includes
EDITION_DIR			=	./line_edition/
DIR_AUTO 			= 	completion_dynamique/

LIBFT_DIR			=	./libft
LIBFT_NAME			=	$(LIBFT_DIR)/libft.a
LIBFT_INCLUDE_DIR	=	$(LIBFT_DIR)/includes

COMPILER			=	gcc
C_FLAGS				=	-g3 -O3 -Wall -Wextra -Werror
LFLAGS				=	-L$(LIBFT_DIR) -l$(LIBFT)


################# 		COMPLETION EDITION PART 		#######################

FILES_EDITION 		=	main.c catch_key.c 	cursor_move.c \
						init.c copy_cut_past.c line_edition.c print_line.c \
						return_key.c signal.c termios.c free_term.c

FILES_COMPLETION	=	detect_auto_completion.c get_files.c match_elements.c \
						set_path.c display_completion.c build_list.c \
						set_sentence.c free_auto_completion.c \
						tools.c set_path_second_part.c

SRC_COMPLETION_EDIT	=	$(addprefix $(EDITION_DIR), $(FILES_EDITION)) \
						$(addprefix $(DIR_AUTO), $(FILES_COMPLETION))

BIN_COMPLETION_EDIT	= 	$(FILES_EDITION:.c=.o) $(FILES_COMPLETION:.c=.o) 

################# 		END COMPLETION EDITION PART 	#######################

################# 		GLOBING PART		###################################

GLOBING = ./globing/
REDIR = redirections/
SBRACK = globing/square_brackets/
CBRACK = globing/curly_brackets/
WILDCARDS = globing/wildcards/
UTILS_1 = globing/square_brackets/sbracket_utils/
UTILS_2 = globing/curly_brackets/cbracket_utils/

FILES_GLOBING	= 	glob_parser.c get_path.c verif_tokens.c recreate_token_string.c \
					replace_env_var.c

FILES_SBRACK 	= 	hub_sbracket.c fill_tabs.c init_tabs.c category_bracket.c \
					sbracket_list.c

FILES_CBRACK 	= 	hub_cbracket.c fill_clist.c cbracket_list.c \
					cbracket_errors.c expansion.c print_clist.c \

FILES_UTILS_1 	= 	catch_dash.c check_rng.c clean_brackets.c \
					count_brackets.c get_functions.c str_nodouble.c

FILES_UTILS_2 	= 	commas_utils.c algo_imbricated.c imbric_utils.c \
					get_imbric_patterns.c cbracket_utils.c \
					imbric_utils2.c double_brck.c expansion_utils.c

FILES_WILDCARDS = 	hub_final.c wildcards_tokens.c wildcards_utils.c \
					wildcards_utils2.c wild_lst_tools.c check_file.c \

SRC_GLOBING 	= 	$(addprefix $(GLOBING), $(FILES_GLOBING)) \
					$(addprefix $(SBRACK), $(FILES_SBRACK)) \
					$(addprefix $(CBRACK), $(FILES_CBRACK)) \
					$(addprefix $(UTILS_1), $(FILES_UTILS_1)) \
					$(addprefix $(UTILS_2), $(FILES_UTILS_2)) \
					$(addprefix $(WILDCARDS), $(FILES_WILDCARDS)) \

BIN_GLOBING 	= 	$(FILES_GLOBING:.c=.o) $(FILES_REDIR:.c=.o) \
					$(FILES_SBRACK:.c=.o) $(FILES_CBRACK:.c=.o) \
					$(FILES_UTILS_1:.c=.o) $(FILES_UTILS_2:.c=.o) \
					$(FILES_WILDCARDS:.c=.o)
		
################# 		END GLOBING PART		###############################

################# 			PARSER PART			###############################
PARSER = ./Lexer_Parser/srcs/

FILES_PARSER 	= 	backslash_escape.c free_tree.c \
					isallspace.c lexer_check.c parser_distrib.c parse.c \
					start_parse.c tree.c token_functions.c prompt_quote.c \
					quote_functions.c quote_functions_2.c error_parse.c \
					check_heredoc.c

SRC_PARSER  	= 	$(addprefix $(PARSER), $(FILES_PARSER))

BIN_PARSER 		= 	$(FILES_PARSER:.c=.o)

################# 		END PARSER PART			###############################

#################		BUILTIN PART 			###############################
BUILTIN 		= 	./builtins/

FILES_BUILTIN 	= 	echo.c env.c setenv.c unsetenv.c cd.c path_converter.c \
					exit.c cd_tools.c

SRC_BUILTIN  	= 	$(addprefix $(BUILTIN), $(FILES_BUILTIN))

BIN_BUILTIN 	= 	$(FILES_BUILTIN:.c=.o)

#################		END BUILTIN PART 		###############################


#################		HISTORY PART 			###############################

HISTORY 		= 	./history/

FILES_HISTORY 	= 	error.c event.c ft_history.c ft_history_options.c \
					historic.c histsize.c lst_tools.c history_lexing.c \
					event_tools.c

SRC_HISTORY 	= 	$(addprefix $(HISTORY), $(FILES_HISTORY))

BIN_HISTORY 	= 	$(FILES_HISTORY:.c=.o)

#################		END HISTORY PART 		###############################

#################		EXECUTION PART 			###############################

EXECUTION 		= 	./execution/

FILES_EXECUTION =	distrib_functions.c exec_tree.c binary_tree_parser.c \
					env_to_tab.c exec_utils.c exec_pipe.c exec_redir.c \
					redir_utils.c

SRC_EXECUTION 	= 	$(addprefix $(EXECUTION), $(FILES_EXECUTION))

BIN_EXECUTION 	= 	$(FILES_EXECUTION:.c=.o)

#################		END EXECUTION PART 		###############################


INCLUDES 	= -I$(LIBFT_INCLUDE_DIR) -I$(INCLUDE_DIR) -I$(PARSER)../includes/
ALL_SRCS 	= $(SRC_COMPLETION_EDIT) $(SRC_GLOBING) $(SRC_PARSER) $(SRC_BUILTIN) $(SRC_HISTORY) $(SRC_EXECUTION)
ALL_BINS 	= $(BIN_COMPLETION_EDIT) $(BIN_GLOBING) $(BIN_PARSER) $(BIN_BUILTIN) $(BIN_HISTORY) $(BIN_EXECUTION)
EXTENSIONS 	= $(LIBFT_DIR)/libft.a $(LIBFT_DIR)/libftprintf.a 

all: $(NAME)

lib:
	make -C libft

$(NAME): lib
	gcc $(C_FLAGS) $(INCLUDES) $(ALL_SRCS) -Incurses -c
	gcc $(C_FLAGS) $(ALL_BINS) $(EXTENSIONS) -ltermcap -o $(NAME)
	mkdir bin_folder
	mv $(ALL_BINS) bin_folder

clean_lib:
	make -C $(LIBFT_DIR) clean

clean: clean_lib
	rm -rf bin_folder

fclean_lib: clean_lib
	make -C $(LIBFT_DIR) fclean

fclean: clean fclean_lib
	rm -rf $(NAME)
	sh ./rm_files.sh


re: fclean all

re_lib: fclean_lib lib