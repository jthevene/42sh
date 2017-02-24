# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apinho <apinho@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/24 18:13:29 by apinho            #+#    #+#              #
#    Updated: 2017/02/24 18:21:04 by apinho           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_printf

LFT = ../

L = ./libftprintf/

S = ./srcs/

C = ./srcs/calls/

FT_PRINTF = ./ft_printf/

LIBSRC = $(L)ftp_putbase.c $(L)ftp_putbase_long.c \
	$(L)ftp_putchar.c $(L)ftp_putnbr.c $(L)ftp_putnbr_long.c \
	$(L)ftp_putstr.c $(L)ftp_strlen.c $(L)ftp_putwchar.c \
	$(L)ftp_putwstr.c

SRC = $(S)ft_check_valid.c $(S)ft_convert_length.c $(S)ft_detection.c \
	$(S)ft_printf.c

CALLS = $(C)call_purcent.c $(C)call_putadress.c $(C)call_putbase.c \
		$(C)call_putbase_long.c $(C)call_putchar.c $(C)call_putnbr.c \
		$(C)call_putnbr_long.c $(C)call_putstr.c $(C)call_putwchar.c \
		$(C)call_putwstr.c $(C)ft_add_spaces.c


SRCBIN = ftp_putbase.o ftp_putbase_long.o ftp_putchar.o ftp_putnbr.o \
		ftp_putnbr_long.o ftp_putstr.o ftp_strlen.o \
		call_purcent.o ftp_putwchar.o ftp_putwstr.o \
		call_putadress.o call_putbase.o call_putbase_long.o call_putchar.o \
		call_putnbr.o call_putnbr_long.o call_putstr.o call_putwchar.o \
		call_putwstr.o ft_add_spaces.o ft_check_valid.o ft_convert_length.o \
		ft_detection.o ft_printf.o

SRCBIN_L = $(L)ftp_putbase.o $(L)ftp_putbase_long.o $(L)ftp_putchar.o \
		$(L)ftp_putnbr.o $(L)ftp_putnbr_long.o $(L)ftp_putstr.o \
		$(L)ftp_strlen.o $(L)ftp_putwchar.o $(L)ftp_putwstr.o \
		$(L)call_purcent.o $(L)call_putadress.o \
		$(L)call_putbase.o $(L)call_putbase_long.o $(L)call_putchar.o \
		$(L)call_putnbr.o $(L)call_putnbr_long.o $(L)call_putstr.o \
		$(L)call_putwchar.o $(L)call_putwstr.o $(L)ft_add_spaces.o \
		$(L)ft_check_valid.o $(L)ft_convert_length.o $(L)ft_detection.o \
		$(L)ft_printf.o

LFT_BIN = $(LFT)ft_atoi.o $(LFT)ft_bzero.o $(LFT)ft_isalnum.o $(LFT)ft_isalpha.o \
		$(LFT)ft_isascii.o $(LFT)ft_isdigit.o $(LFT)ft_isprint.o $(LFT)ft_itoa.o \
		$(LFT)ft_memalloc.o $(LFT)ft_memccpy.o $(LFT)ft_memchr.o $(LFT)ft_memcmp.o \
		$(LFT)ft_memcpy.o $(LFT)ft_memdel.o $(LFT)ft_memmove.o $(LFT)ft_memset.o \
		$(LFT)ft_putchar.o $(LFT)ft_putchar_fd.o $(LFT)ft_putendl.o $(LFT)ft_putendl_fd.o \
		$(LFT)ft_putnbr.o $(LFT)ft_putnbr_fd.o $(LFT)ft_putstr.o $(LFT)ft_putstr_fd.o \
		$(LFT)ft_strcat.o $(LFT)ft_strchr.o $(LFT)ft_strclr.o $(LFT)ft_strcmp.o \
		$(LFT)ft_strcpy.o $(LFT)ft_strdel.o $(LFT)ft_strdup.o $(LFT)ft_strequ.o \
		$(LFT)ft_striter.o $(LFT)ft_striteri.o $(LFT)ft_strjoin.o $(LFT)ft_strlcat.o \
		$(LFT)ft_strlen.o $(LFT)ft_strmap.o $(LFT)ft_strmapi.o $(LFT)ft_strncat.o $(LFT)ft_strncmp.o \
		$(LFT)ft_strncpy.o $(LFT)ft_strnequ.o $(LFT)ft_strnew.o $(LFT)ft_strnstr.o $(LFT)ft_strrchr.o \
		$(LFT)ft_strsplit.o $(LFT)ft_strstr.o $(LFT)ft_strsub.o $(LFT)ft_strtrim.o $(LFT)ft_tolower.o \
		$(LFT)ft_toupper.o $(LFT)ft_lstnew.o $(LFT)ft_lstdelone.o $(LFT)ft_lstdel.o $(LFT)ft_lstadd.o \
		$(LFT)ft_lstiter.o $(LFT)ft_lstmap.o $(LFT)ft_sqrt.o $(LFT)ft_capitalize.o $(LFT)ft_printbase.o \
		$(LFT)ft_printhex.o $(LFT)ft_strtolower.o $(LFT)ft_strtoupper.o $(LFT)ft_abs.o \
		$(LFT)ft_print_list.o $(LFT)ft_lstadd_bottom.o $(LFT)ft_itoabase.o $(LFT)ft_putwchar.o \
		$(LFT)ft_atoibase.o $(LFT)ft_recursive_pow.o $(LFT)ft_putwstr.o $(LFT)get_next_line.o \
		$(LFT)ft_putnbrendl.o $(LFT)ft_isspace.o $(LFT)ft_putchar_int.o $(LFT)ft_nbrlen.o \
		$(LFT)ft_lstaddend.o

CC = gcc -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	@printf "\033[31mCompilation des sources de la libft\n\033[0m"
#	@make -C ../
	@printf "\033[31mCompilation de la libftprintf.a\033[0m "
	@$(CC) -c ../includes/libft.h $(LIBSRC) $(SRC) $(CALLS)
	@mv $(SRCBIN) $(L)
	@ar rcs libftprintf.a $(SRCBIN_L) $(LFT_BIN) ./includes/ft_printf.h
	@mv libftprintf.a ..
	@echo "\033[32m[OK]\033[0m"

clean:
	@printf "\033[31mNettoyage des dossiers\033[0m "
	@rm -rf $(SRCBIN_L)
	@echo "\033[32m[OK]\033[0m"

fclean: clean
	@printf "\033[31mNettoyage de tous les dossiers\033[0m "
	@rm -rf ../libftprintf.a
	@echo "\033[32m[OK]\033[0m"

re: fclean all