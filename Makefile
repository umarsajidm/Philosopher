NAME = philo

CC = cc

CFLAGS = -Werror -Wextra -Wall

SRC = main.c \
	utilities.c

OBJ = $(SRC:.c=.o) 

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBj)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re