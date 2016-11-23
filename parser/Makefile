
CC =	gcc

NAME =  ft_parse

SRC  =  ./free_tree.c \
	./tree.c \
	./search.c \
	./main.c \
	./parse.c \
	./parse2.c \
	./get_next_line.c \

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
