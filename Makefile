CC=cc
CFLAGS=-Wall -Wextra -Werror
NAME=pipex
SRC_FILES=pipex.c all_format.c alpha.c ft_printf.c ft_split.c ft_strjoin.c ft_strlen.c numerique.c ft_execve.c ft_path.c utils.c
OBJ_FILES=$(SRC_FILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ_FILES)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
