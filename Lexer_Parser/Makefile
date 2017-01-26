CC =	gcc

NAME =  21sh

SRC  =  ./srcs/lexer_check.c \
	./srcs/main.c \
	./srcs/isallspace.c \
	./srcs/get_next_line.c \
	./srcs/backslash_escape.c \
	./srcs/free_tree.c \
	./srcs/tree.c \
	./srcs/parse.c \
	./srcs/start_parse.c \

OBJ =	$(SRC:.c=.o)

CFLAGS	+= -Wall -Wextra -Werror
LDFLAGS	+= -Llibft -lft -ltermcap

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(OBJ)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all
