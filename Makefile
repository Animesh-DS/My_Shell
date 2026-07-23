TARGET = shell
OBJ = main.c parse_input.c buildins.c
CFLAGS = -Wall -Wextra -Werror
CC = gcc

all:
	$(CC) -o $(TARGET) $(OBJ)

clean:
	rm -f *-o

fclean: clean
	rm -f $(TARGET)

re: fclean all