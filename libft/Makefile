# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/24 18:13:29 by hjacque           #+#    #+#              #
#    Updated: 2017/03/23 18:43:25 by sgaudin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

#---------------------------- Sources libft et GNL ----------------------------#

SRC = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
ft_isprint.c ft_itoa.c ft_memalloc.c ft_memccpy.c ft_memchr.c ft_memcmp.c \
ft_memcpy.c ft_memdel.c ft_memmove.c ft_memset.c ft_putchar.c ft_putchar_fd.c \
ft_putendl.c ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c ft_putstr.c \
ft_putstr_fd.c ft_strcat.c ft_strchr.c ft_strclr.c ft_strcmp.c ft_strcpy.c \
ft_strdel.c ft_strdup.c ft_strequ.c ft_striter.c ft_striteri.c ft_strjoin.c \
ft_strlcat.c ft_strlen.c ft_strmap.c ft_strmapi.c ft_strncat.c ft_strncmp.c \
ft_strncpy.c ft_strnequ.c ft_strnew.c ft_strnstr.c ft_strrchr.c ft_strsplit.c \
ft_strstr.c ft_strsub.c ft_strtrim.c ft_tolower.c ft_toupper.c ft_lstnew.c \
ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c ft_lstmap.c ft_sqrt.c \
ft_capitalize.c ft_printbase.c ft_printhex.c ft_strtolower.c ft_strtoupper.c \
ft_abs.c ft_print_list.c ft_lstadd_bottom.c ft_itoabase.c ft_putwchar.c \
ft_atoibase.c ft_recursive_pow.c ft_putwstr.c get_next_line.c ft_putnbrendl.c \
ft_isspace.c ft_putchar_int.c ft_nbrlen.c ft_lstaddend.c ft_puttab.c \
ft_get_nbr.c ft_lstaddback.c ft_ltoa.c ft_putendl_exit.c ft_putendl_fd_exit.c \
ft_putnbrulong.c ft_putstrspace.c ft_count_tab.c \
ft_putstrtime.c ft_putstrtimespace.c ft_realloc.c ft_strjoinchar.c \
ft_strjoinfree.c ft_strdupfree.c ft_tabdup.c size_bin.c ft_strndup.c \
ft_str_replace.c ft_putnbrprec.c ft_putnbr_ftprintf.c

BINARY = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	@printf "\033[31mCompilation des sources\033[0m"
	@gcc -Wall -Wextra -Werror -c -I./includes/ $(SRC)
	@printf "\033[32mDone !\033[0m\n"
	@printf "\033[31mCreation et indexage de libft.a\n\033[0m"
	@ar rcs $(NAME) $(BINARY)
	@printf "\033[31mCreation et indexage de libftprintf.a\033[0m"
	@printf "\033[32mDone !\033[0m\n"

clean:
	@printf "\033[31mSuppression des fichiers .o\033[0m"
	@rm -rf $(BINARY)
	@printf "\033[32mDone !\033[0m\n"

fclean: clean
	@printf "\033[31mSuppression de libft.a\033[0m"
	@rm -rf $(NAME)
	@printf "\033[32mDone !\033[0m\n"

re: fclean all