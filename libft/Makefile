# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jthevene <jthevene@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/11 15:52:42 by jthevene          #+#    #+#              #
#    Updated: 2016/05/24 15:48:36 by jthevene         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_memccpy.c	ft_putnbr_fd.c	ft_striteri.c ft_strrchr.c ft_lstmap.c \
		ft_memchr.c	ft_putstr.c	ft_strjoin.c ft_strsplit.c ft_lstmap.c \
		ft_memcmp.c	ft_putstr_fd.c ft_strlcat.c ft_strstr.c ft_lstaddend.c\
		ft_atoi.c ft_memcpy.c ft_strcat.c ft_strlen.c ft_strsub.c ft_lstlen.c \
		ft_bzero.c ft_memdel.c ft_strchr.c ft_strmap.c ft_strtrim.c \
		ft_isalnum.c ft_memmove.c ft_strclr.c ft_strmapi.c ft_tolower.c \
		ft_isalpha.c ft_memset.c ft_strcmp.c ft_strncat.c ft_toupper.c \
		ft_isascii.c ft_putchar.c ft_strcpy.c ft_strncmp.c ft_lstadd.c \
		ft_isdigit.c ft_putchar_fd.c ft_strdel.c ft_strncpy.c ft_lstiter.c \
		ft_isprint.c ft_putendl.c ft_strdup.c ft_strnequ.c ft_lstdel.c \
		ft_itoa.c ft_putendl_fd.c ft_strequ.c ft_strnew.c ft_lstdelone.c \
		ft_memalloc.c ft_putnbr.c ft_striter.c ft_strnstr.c ft_lstnew.c \
		ft_count_tab.c ft_nbrlen.c ft_swap.c get_next_line.c \
		ft_strpathjoin.c ft_putchar_int.c


OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME) :
	@gcc -c $(FLAGS) $(SRC) -I.
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

clean :
	@rm -f $(OBJ)

fclean : clean
	@rm -f $(NAME)

re : fclean all
