NAME = philo

CC = cc

CFLAGS = -Werror -Wextra -Wall

SRC = *.c

OBJ = $(SRC:.c=.o) 

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBj)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re