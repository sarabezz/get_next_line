NAME = get_next_line.a
EXEC = get_next_line

# Archivos fuente
SRC = get_next_line.c get_next_line_utils.c
OBJ = $(SRC:.c=.o)

# Flags de compilación
CFLAGS = -Wall -Wextra -Werror

# Comandos de compilación
CC = gcc
AR = ar rcs

# Regla para compilar la biblioteca estática
all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

# Regla para compilar el archivo ejecutable
$(EXEC): $(OBJ) main.o
	$(CC) $(CFLAGS) $(OBJ) main.o -o $(EXEC)

# Limpiar los archivos objeto
clean:
	@rm -f $(OBJ) main.o

# Limpiar todo (archivos objeto + biblioteca estática)
fclean: clean
	@rm -f $(NAME) $(EXEC)

# Regenerar todo
re: fclean all
