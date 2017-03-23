#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hjacque <hjacque@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/03 11:53:37 by hjacque           #+#    #+#              #
#    Updated: 2017/03/23 17:54:53 by sgaudin          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME =	libftprintf.a

SRC	 =	./short.c \
		./conv.c \
		./range.c \
		./ft_printf.c \
		./tools.c \
		./castop.c \
		./printfpourcent.c \
		./printfc.c \
		./printfd.c \
		./printfi.c \
		./printfo.c \
		./printfp.c \
		./printfs.c \
		./printfu.c \
		./printfx.c \

DEST =	./short.o \
		./conv.o \
		./range.o \
		./ft_printf.o \
		./tools.o \
		./castop.o \
		./printfpourcent.o \
		./printfc.o \
		./printfd.o \
		./printfi.o \
		./printfo.o \
		./printfp.o \
		./printfs.o \
		./printfu.o \
		./printfx.o \

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	@gcc $(CFLAGS) -c $(SRC)
	@ar rc temppf.a $(DEST)
	@ranlib temppf.a
	@libtool -static -o $(NAME) ../libft.a temppf.a
	@rm -rf temppf.a

clean:
	@rm -f $(DEST)

fclean: clean
	@rm -f $(NAME)

re: fclean all
