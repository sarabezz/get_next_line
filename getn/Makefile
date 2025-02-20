NAME = get_next_line.a

all:
	gcc -Wall -Wextra -Werror -c get_next_line.c get_next_line_utils.c
	ar rcs $(NAME) get_next_line.o get_next_line_utils.o

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all
