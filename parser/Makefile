
CC =	gcc

NAME =  ft_parse

SRC  =  ./srcs/free_tree.c \
	./srcs/pipe.c \
	./srcs/fork.c \
	./srcs/tree.c \
	./srcs/search.c \
	./srcs/main.c \
	./srcs/parse.c \
	./srcs/parse2.c \
	./srcs/get_next_line.c \

OBJ =	$(SRC:.c=.o)

CFLAGS	+= -Wall -Wextra -Werror
LDFLAGS	+= -Llibft -lft -ltermcap

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C libft
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(OBJ)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean all
