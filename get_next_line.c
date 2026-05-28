/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarabermudez <sarabermudez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:41:33 by sarabermude       #+#    #+#             */
/*   Updated: 2025/03/03 18:28:10 by sarabermude      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*buffer_comprobation(char *buffer, char *buf, int length)
{
	char	*b;

	buf[length] = '\0';
	b = ft_strjoin(buffer, buf);
	free(buffer)
	if (!b)
		return (NULL);
	return (b);
}

static char	*rd(int fd, char *buffer)
{
	char	buf[BUFFER_SIZE + 1];
	int		length;

	if (!buffer)
		buffer = ft_strdup("");
	while (1)
	{
		length = read(fd, buf, BUFFER_SIZE);
		if (length < 0)
		{
			free(buffer);
			return (NULL);
		}
		if (length == 0)
			break ;
		buffer = buffer_comprobation(buffer, buf, length);
		if (!buffer)
			return (NULL);
	}
	return (buffer);
}

static char	*get_line(char *buffer)
{
	size_t	i;
	char	*line;

	if (!buffer)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = malloc(i + (buffer[i] == '\n') + 1);
	if (!line)
		return (NULL);
	ft_memcpy(line, buffer, i + (buffer[i] == '\n'));
	line[i + (buffer[i] == '\n')] = '\0';
	return (line);
}

static char	*separate(char *buffer)
{
	char	*new_buffer;
	size_t	i;

	if (!buffer)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i] || !buffer[i + 1])
	{
		free(buffer);
		return (NULL);
	}
	new_buffer = ft_strdup(buffer + i + 1);
	if (!new_buffer)
	{
		free(buffer);
		return (NULL);
	}
	free(buffer);
	return (new_buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = rd(fd, buffer);
	if (!buffer || !*buffer)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	line = get_line(buffer);
	if (!line)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	buffer = separate(buffer);
	return (line);
}

/*
#include "get_next_line.h"
#include <fcntl.h>  // Para el uso de open()
#include <stdio.h>   // Para printf()

int main(void)
{
    int fd;
    char *line;

    fd = open("prueba.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("Error abriendo el archivo");
        return (1);
    }
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}


int main(void)
{
    char *line;

    while ((line = get_next_line(0)) != NULL)
    {
        printf("%s", line);
        free(line);
	}

    return (0);
}
*/

/*
CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC = get_next_line.c get_next_line_utils.c
OBJ = $(SRC:.c=.o)
NAME = gnl.a

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
*/
